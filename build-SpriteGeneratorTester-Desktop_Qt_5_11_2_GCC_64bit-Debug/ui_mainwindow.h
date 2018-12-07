/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *smallSpriteButton;
    QPushButton *mediumSprietButton;
    QPushButton *largeSpriteButton;
    QPushButton *veryLargeSpriteButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(807, 666);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(190, 10, 600, 600));
        smallSpriteButton = new QPushButton(centralWidget);
        smallSpriteButton->setObjectName(QStringLiteral("smallSpriteButton"));
        smallSpriteButton->setGeometry(QRect(20, 40, 161, 21));
        mediumSprietButton = new QPushButton(centralWidget);
        mediumSprietButton->setObjectName(QStringLiteral("mediumSprietButton"));
        mediumSprietButton->setGeometry(QRect(19, 70, 161, 21));
        largeSpriteButton = new QPushButton(centralWidget);
        largeSpriteButton->setObjectName(QStringLiteral("largeSpriteButton"));
        largeSpriteButton->setGeometry(QRect(19, 100, 161, 21));
        veryLargeSpriteButton = new QPushButton(centralWidget);
        veryLargeSpriteButton->setObjectName(QStringLiteral("veryLargeSpriteButton"));
        veryLargeSpriteButton->setGeometry(QRect(19, 130, 161, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 807, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        smallSpriteButton->setText(QApplication::translate("MainWindow", "Generate Small Sprite", nullptr));
        mediumSprietButton->setText(QApplication::translate("MainWindow", "Generate Meidum Sprite", nullptr));
        largeSpriteButton->setText(QApplication::translate("MainWindow", "Generate Large Sprite", nullptr));
        veryLargeSpriteButton->setText(QApplication::translate("MainWindow", "Generate Very Large Sprite", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
