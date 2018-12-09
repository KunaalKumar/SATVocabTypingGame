#include "loadwords.h"

std::vector<std::string> LoadWords::allHardWords;
std::map<int, std::vector<std::string>> LoadWords::allEasyWords;
std::vector<std::string> LoadWords::roundWords;
int LoadWords::nextWordIndex;

void LoadWords::importWords(bool isHard)
{
    std::ifstream stream;
    if (isHard)
    {
        stream.open("..//src/dictionary/sat");
    }
    else
    {
        stream.open("..//src/dictionary/words");
     }

     if (!stream.is_open())
     {
         //TODO: Handle
     }
     else
     {
         if (isHard)
         {

             std::string word;
             while (!stream.eof())
             {
                 std::getline(stream, word);
                 allHardWords.push_back(word);
              }
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
                     allEasyWords[length++] = wordsOfSameLength;
                     wordsOfSameLength.clear();
                 }
                 else
                 {
                     wordsOfSameLength.push_back(word);
                 }
              }
         }
    }
    srand(time(0));
}

void LoadWords::resetWords()
{
    allEasyWords.clear();
    allHardWords.clear();
    roundWords.clear();
}

void LoadWords::createRoundWords(int round, bool hard)
{
    if (hard)
    {
        int numWords = round * 10;
        for (int i = 0; i < numWords; i++)
        {
           long wordIndex = rand() % allHardWords.size();
           std::string word = allHardWords.at(wordIndex);
           roundWords.push_back(word);
        }

        nextWordIndex = 0;
    }
    else
    {
        int numWords = round * 10;
        for (int i = 0; i < numWords; i++)
        {
           long wordLength = (rand() % round + 3) % 14;
           long wordIndex = rand() % allEasyWords[wordLength].size();

           std::string word = allEasyWords[wordLength].at(wordIndex);
           roundWords.push_back(word);
        }

        nextWordIndex = 0;
    }

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
