#include "loadwords.h"

std::map<int, std::vector<std::string>> LoadWords::allWords;
std::vector<std::string> LoadWords::roundWords;
int LoadWords::nextWordIndex;

void LoadWords::importWords()
{
    std::ifstream stream;
     stream.open("..//src/dictionary/words");
     if (!stream.is_open())
     {
         //TODO: Handle
     }
     else
     {
        std::string word;
        std::vector<std::string> wordsOfSameLength;
        int length = 3;
        while (!stream.eof())
        {
            std::getline(stream, word);
            if (word.length() == 0)
            {
                allWords[length++] = wordsOfSameLength;
                wordsOfSameLength.clear();
            }
            else
            {
                wordsOfSameLength.push_back(word);
            }
         }
    }
}

void LoadWords::createRoundWords(int round)
{
    for (int i = 0; i < 20; i++)
    {
       srand(time(0));
       long wordLength = rand() % round + 3;
       long wordIndex = rand() % allWords[wordLength].size();

       std::string word = allWords[wordLength].at(wordIndex);
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

void sortWordTxtFile(QFile target)
{
     std::fstream stream;
     //stream.open("../GameLib/temp");

     std::vector<std::string> words;
     //Save all words from user file into a vector
     if (target.open(QIODevice::ReadOnly))
     {
        std::string line;
        QTextStream reader(&target);
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

     stream.open("../src/dictionary/userWords");

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
