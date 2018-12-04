/*
 * Purple Picnic Turtles
 *
 * Creator: - Nathan Boehm
 *
 * project.cpp
 */

#include "project.h"
#include<3rdParty/qtgifimage/src/gifimage/qgifimage.h>


Project::Project(int frameSize):
    framePixelSize(frameSize)
{
    currentFrame = 0;
    addNewFrame();
    previewImage = createNewFrame();

    canvas = new Canvas(frameSize, frames[currentFrame]);
    animation = new SpriteAnimation(&frames);
    tools = new Tools(frames[currentFrame], previewImage);


    QObject::connect(canvas, SIGNAL(mousePressed(int, QPointF)),
                     tools,  SLOT(handleMousePress(int, QPointF)) );

    QObject::connect(canvas, SIGNAL(mouseMoved(int, QPointF)),
                     tools,  SLOT(handleMouseMove(int, QPointF)) );

    QObject::connect(canvas, SIGNAL(mouseReleased(int, QPointF)),
                     tools,  SLOT(handleMouseRelease(int, QPointF)) );

    QObject::connect(tools, SIGNAL(imageUpdated()),
                     this,  SLOT(updateImage()) );

    QObject::connect(tools, SIGNAL(previewImageUpdated()),
                     this,  SLOT(updatePreviewImage()) );
}

Project::~Project()
{
    delete canvas;
    delete tools;
    for (QImage* image : frames) { delete image; }
    delete animation;
    delete frameView;
}

void Project::setFrameView(QTableWidget* widget)
{
    this->frameView = new FrameView(widget, &frames);
}

void Project::setCurrentFrame(int frameNumber)
{
    frameView->updateFrame(currentFrame);
    currentFrame = frameNumber;
    canvas->setImage(frames[currentFrame]);
    tools->setImage(frames[currentFrame]);
}

QImage* Project::createNewFrame()
{
    QImage* image = new QImage(framePixelSize, framePixelSize, QImage::Format_ARGB32);
    image->fill(Qt::transparent);
    return image;
}

void Project::addNewFrame()
{
    frames.push_back(createNewFrame());
    if (frames.size() > 1)
    {
        setCurrentFrame(frames.size() - 1);
        frameView->addFrame();
    }
}


/*UI Helpers*/


void Project::setActiveTool(Global::Tool tool)
{
    tools->setSelectedTool(tool);
}

SpriteAnimation* Project::getAnimation()
{
    return animation;
}

Canvas* Project::getCanvas()
{
    return canvas;
}

void Project::handleGridlinesToggled()
{
    canvas->toggleGridlines();
}

void Project::handleAnimationSliderValueChanged(int value)
{
    animation->setFrameRate(value);
}

void Project::handleBrushSizeChanged(int value)
{
    tools->setBrushSize(value);
}

void Project::handleEraserSizeChanged(int value)
{
    tools->setEraserSize(value);
}

void Project::setColorLabel(ColorLabel* leftLabel, ColorLabel* rightLabel)
{
    this->leftColorLabel = leftLabel;
    this->rightColorLabel = rightLabel;

    QObject::connect(leftColorLabel, SIGNAL(colorChanged(QColor, ColorLabel*)),
                     this, SLOT(handleColorChanged(QColor, ColorLabel*)));

    QObject::connect(rightColorLabel, SIGNAL(colorChanged(QColor, ColorLabel*)),
                     this, SLOT(handleColorChanged(QColor, ColorLabel*)));

    // Default starting colors
    handleColorChanged(QColor(0, 0, 0), leftColorLabel);
    handleColorChanged(QColor(255, 0, 0), rightColorLabel);
}


/*Slots*/


void Project::handleColorChanged(QColor color, ColorLabel* label)
{
    if(label == leftColorLabel)
    {
        tools->setLeftSelectedColor(color.rgba());
    }
    if(label == rightColorLabel)
    {
        tools->setRightSelectedColor(color.rgba());
    }

    QImage image(1, 1, QImage::Format_ARGB32);
    image.setPixelColor(0, 0, color);
    label->setPixmap(QPixmap().fromImage(image.scaled(150, 50)));
}

void Project::updateImage()
{
    canvas->setImage(frames[currentFrame]);
    frameView->updateFrame(currentFrame);
}

void Project::updatePreviewImage()
{
    canvas->setImage(previewImage);
}


/*File IO*/


void Project::save(QString filename)
{
    if ( ! filename.contains(".ssp")) {filename = filename.append(".ssp");}
    QFile saveFile(filename);
    saveFile.open((QIODevice::WriteOnly | QIODevice::Text));
    QTextStream writer(&saveFile);

    writer << framePixelSize << " " << framePixelSize << '\n';
    writer << frames.size() << '\n';

    for (QImage* image : frames)
    {
        for (int y = 0; y < framePixelSize; y++)
        {
            for (int x = 0; x < framePixelSize; x++)
            {
                QColor color = image->pixelColor(y,x);
                writer << color.red() << " " << color.green() << " "
                       << color.blue() << " " << color.alpha() << " ";

            }
            writer << '\n';
        }
    }
    saveFile.close();
}

void Project::load(QString filename)
{
    QFile loadFile(filename);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Opening file failed!";
    }
    else
    {
        frames.clear();
        QTextStream reader(&loadFile);
        setNewFrameSize(reader.readLine().split(" ")[0].toInt());
        int numFrames = reader.readLine().split(" ")[0].toInt();

        for (int i = 0; i < numFrames; i++)
        {
            QImage* frame = new QImage(framePixelSize, framePixelSize, QImage::Format_ARGB32);

            for (int y = 0; y < framePixelSize; y++)
            {
                QString line = reader.readLine();

                for (int x = 0; x < framePixelSize; x++)
                {
                    QStringList lineArr = line.split(" ");
                    int r = lineArr[x * 4].toInt();
                    int g = lineArr[x * 4 + 1].toInt();
                    int b = lineArr[x * 4 + 2].toInt();
                    int a = lineArr[x * 4 + 3].toInt();
                    frame->setPixelColor(QPoint(y, x), QColor(r, g, b, a));
                }
            }
            frames.push_back(frame);
        }
        frameView->loadFrames();
        setCurrentFrame(frames.size() - 1);
        loadFile.close();
    }
}

void Project::exportGIF(QString filename)
{
    QGifImage gif(QSize(windowSize, windowSize));

    QVector<QRgb> ctable;

    gif.setGlobalColorTable(ctable, QColor(Qt::white));
    gif.setDefaultTransparentColor( QColor(Qt::white));

    if (frameRate == 0)
    {
        frameRate = 1;
    }
    gif.setDefaultDelay(1000/frameRate);

    for(int i = 0; i < frames.size(); i++)
    {

         QImage currentImage = frames[i]->copy();

         for(int i = 0; i < currentImage.width(); i++)
         {
             for(int j = 0; j < currentImage.height(); j++)
             {
                 if(currentImage.pixelColor(i, j) == Qt::transparent ||
                         currentImage.pixelColor(i, j) == QColor(255, 255, 255, 0))
                 {
                     currentImage.setPixelColor(i, j, QColor(Qt::white));
                 }
             }
         }

         gif.addFrame(currentImage.scaled(windowSize,windowSize), QPoint(0, 0));
     }

     gif.save(filename);
}

void Project::setNewFrameSize(int frameSize)
{
    framePixelSize = frameSize;
    canvas->setNewFrameSize(frameSize);
}
