#include "loadwords.h"

LoadWords::LoadWords()
{

}

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
       int wordLength = rand() % round + 3;
       int wordIndex = rand() % allWords[wordLength].size();

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

//void sortWordTxtFile()
//{
//    std::fstream stream;
//     stream.open("../GameLib/temp");
//     std::vector<std::string> words;
//     if (stream.is_open())
//     {
//        std::string line;
//        int i = 0;
//        while (!stream.eof())
//        {
//            std::getline(stream, line);
//            if (line.length() > 0)
//            {
//                words.push_back(line);
//            }
//         }
//    }

//     std::sort(words.begin(), words.end(),
//           [](const std::string& lhs, const std::string& rhs)
//            {
//                return lhs.size() == rhs.size() ? lhs < rhs : lhs.size() < rhs.size();
//            });

//     words.erase( unique( words.begin(), words.end() ), words.end() );

//     stream.close();

//     stream.open("../GameLib/words");
//     for (int i = 0; i < words.size(); i++)
//     {
//        stream << words.at(i) << std::endl;
//     }

//    stream.close();
//}
