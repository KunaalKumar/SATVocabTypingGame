#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <QFile>
#include <QTextStream>

class LoadWords
{
    public:
        static void resetWords();
        static void importWords(bool hard);
        static void createRoundWords(int round, bool hard);
        // returns "" if end of round
        static std::string getWord();
        static void sortWordTxtFile(QFile *target);

    private:
        static std::vector<std::string> allHardWords;
        static std::map<int, std::vector<std::string>> allEasyWords;
        static std::vector<std::string> roundWords;
        static int nextWordIndex;
};

#endif // LOAD_H
