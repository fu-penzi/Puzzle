#ifndef SCORE_H
#define SCORE_H


#include "game.h"
#include "gameconfig.h"

#include <string>
#include <vector>

struct FScore
{
    int GameId;
    int RemainingTime;
    int Moves;
    bool bWin;
    EDifficulty Difficulty;
    EMode GameMode;
};

class FPlayerScores
{
public:
    FPlayerScores(std::string ScorePath);

    int GamesPlayed() const;
    int GamesWon() const;
    int GamesLost() const;
    const std::vector<FScore>& Scores() const;

    void AddStartedGame();
    void SaveScore(FGame* Game);

private:
    int GamesPlayed_ = 0;
    int GamesWon_ = 0;
    int GamesLost_ = 0;
    std::vector<FScore> Scores_;

    const std::string ScorePath_;

    void UpdateScoreFile();
    void LoadScoreFile();
};

#endif // SCORE_H
