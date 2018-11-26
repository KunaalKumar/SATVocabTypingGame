#include "gamelib.h"


GameLib::GameLib()
{
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
