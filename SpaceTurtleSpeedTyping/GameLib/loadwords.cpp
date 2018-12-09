#include "loadwords.h"
#include <QDebug>

std::vector<std::string> LoadWords::allWords;
std::vector<std::string> LoadWords::roundWords;
int LoadWords::nextWordIndex;

void LoadWords::importWords()
{
//    QString fileName = "..//src/dictionary/sat";
//    QFile *file = new QFile(fileName);
//    sortWordTxtFile(file);
    std::ifstream stream;
     stream.open("..//src/dictionary/sat");
     if (!stream.is_open())
     {
         //TODO: Handle
     }
     else
     {
        std::string word;
        while (!stream.eof())
        {
            std::getline(stream, word);
            allWords.push_back(word);
         }
    }
    srand(time(0));
}

void LoadWords::createRoundWords(int round)
{
    int numWords = round * 10;
    for (int i = 0; i < numWords; i++)
    {
       long wordIndex = rand() % allWords.size();
       std::string word = allWords.at(wordIndex);
       roundWords.push_back(word);
    }

    nextWordIndex = 0;
}

std::string LoadWords::getWord()
{
    if (nextWordIndex == roundWords.size())
    {
        return "";
    }
    return roundWords.at(nextWordIndex++);
}

void LoadWords::sortWordTxtFile(QFile *target)
{
     std::fstream stream;
     //stream.open("..//src/dictionary/sat");

     std::vector<std::string> words;
     //Save all words from user file into a vector
     if (target->open(QIODevice::ReadOnly))
     {
        std::string line;
        QTextStream reader(target);
        //int i = 0;
        while (!reader.atEnd())
        {
            line = reader.readLine().toLocal8Bit().constData();
            if (line.length() > 0)
            {
                words.push_back(line);
            }
         }
    }
    //Sort the vector
     std::sort(words.begin(), words.end(),
           [](const std::string& lhs, const std::string& rhs)
            {
                return lhs.size() == rhs.size() ? lhs < rhs : lhs.size() < rhs.size();
            });

     words.erase( unique( words.begin(), words.end() ), words.end() );

     //stream.close();

     stream.open("...//src/dictionary/sat1");

     //store it into the folder
     int currentLength = words.at(0).length();
     for (int i = 0; i < words.size(); i++)
     {
         if(currentLength<words.at(i).length()){
             stream << "" <<std::endl;
         }
        stream << words.at(i) << std::endl;
     }

    stream.close();
}
