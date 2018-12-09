#include "stats.h"


Stats::Stats()
{
    round = 0;
    totalTypeCount = 0;
    correctTypeCount = 0;
    totalKillCount = 0;
    killStreak = 0;
}

void Stats::addRound()
{
    round++;
}

int Stats::getRound()
{
    return round;
}

void Stats::addTypeCount(bool isCorrectLetter)
{
    if(isCorrectLetter)
    {
        totalTypeCount++;
        correctTypeCount++;
        killStreak++;
    }
    else
    {
        totalTypeCount++;
        killStreak = 0;
    }
}

double Stats::getCorrectRate()
{
    if(totalTypeCount == 0)
    {
        return 0.0;
    }
    else
    {
        return correctTypeCount / totalTypeCount;
    }
}

int Stats::getTotalType()
{
    return totalTypeCount;
}

int Stats::getCorrectType()
{
    return correctTypeCount;
}

void Stats::addTotalKill()
{
    totalKillCount++;
}

int Stats::getTotalKill()
{
    return totalKillCount;
}

int Stats::getKillStreak()
{
    return killStreak;
}

bool Stats::highScore(bool isGameDone, int score)
{
    bool newHighScore = false;
    if(isGameDone){
        std::ifstream stream;
         stream.open("..//src/ScoreBoard/playerScore");
         //If you cannot open the file
         if (!stream.is_open())
         {
             //TODO: Handle
         }
         //If you can
         else
         {
            std::string word;
            std::vector<std::string> playerScores;
            //Get each score from the file
            while (!stream.eof())
            {
                std::getline(stream, word);
                playerScores.push_back(word);
            }
            stream.close();
            //input the score
            if(playerScores.size()==0){
                playerScores.push_back(std::to_string(score));
            }
            else{
                for(int i=0; i<playerScores.size();i++){
                    if((int)atoi(playerScores[i].c_str())<score){
                        if(i+1==playerScores.size()){
                            newHighScore = true;
                        }
                        std::string temp = std::to_string(score);
                        playerScores[i].insert(i,temp);
                        break;
                    }
                }
            }
            //If there are 4 scores
            if(playerScores.size()==4){
                playerScores.pop_back();
            }
            //write it back to the file
            std::ofstream input;
            input.open("..//src/ScoreBoard/playerScore");
            for(int i=0;i<playerScores.size();i++){
                input<< playerScores[i] +"\n";
            }

        }

    }
    return newHighScore;

}

const std::map<std::string, double>& Stats::getAllStats(){
    statsMap.insert(std::pair<std::string, double>("round", getRound()));
    statsMap.insert(std::pair<std::string, double>("correctRate", getCorrectRate()));
    statsMap.insert(std::pair<std::string, double>("totalKill", getTotalKill()));
    statsMap.insert(std::pair<std::string, double>("killStreak", getKillStreak()));
    statsMap.insert(std::pair<std::string, double>("currentScore", getScore()));
    statsMap.insert(std::pair<std::string, double>("highScore", highScore(true, getScore())));

    return statsMap;
}

int Stats::getScore() {
    //return getRound() * (getCorrectType() + getTotalKill() + getKillStreak());
}
