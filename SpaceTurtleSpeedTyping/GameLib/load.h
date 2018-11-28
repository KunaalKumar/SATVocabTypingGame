#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <fstream>
#include <map>
#include <vector>


class Load
{
    public:
        Load();
        static void importWords();
        static void createRoundWords(int round);
        // returns "" if end of round
        static std::string getWord();
    private:
        static std::map<int, std::vector<std::string>> allWords;
        static std::vector<std::string> roundWords;
        static int nextWordIndex;

};

#endif // LOAD_H
