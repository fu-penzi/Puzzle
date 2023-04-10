#include "playerscores.h"

#include <filesystem>
#include <fstream>
#include <iostream>

FPlayerScores::FPlayerScores(std::string ScorePath)
    : ScorePath_{ScorePath}
{
    LoadScoreFile();
}

int FPlayerScores::GamesPlayed() const
{
    return GamesPlayed_;
}

int FPlayerScores::GamesWon() const
{
    return GamesWon_;
}

int FPlayerScores::GamesLost() const
{
    return GamesLost_;
}

const std::vector<FScore>& FPlayerScores::Scores() const
{
    return Scores_;
}

void FPlayerScores::AddStartedGame()
{
    ++GamesPlayed_;
    UpdateScoreFile();
}

void FPlayerScores::SaveScore(FGame* Game)
{
    if(Game->bWin())
    {
        ++GamesWon_;
    }
    else
    {
        ++GamesLost_;
    }

    FScore Score
    {
        Game->GameId(),
        Game->Time(),
        Game->Moves(),
        Game->bWin(),
        Game->GameConfig().Difficulty(),
        Game->GameConfig().Mode(),
    };
    Scores_.push_back(Score);

    UpdateScoreFile();
}

void FPlayerScores::UpdateScoreFile()
{
    std::ofstream ScoreFile;
    ScoreFile.open(ScorePath_, std::ios::out | std::ofstream::trunc);
    ScoreFile.write(reinterpret_cast<char*>(&GamesPlayed_), sizeof(GamesPlayed_));
    ScoreFile.write(reinterpret_cast<char*>(&GamesWon_), sizeof(GamesWon_));
    ScoreFile.write(reinterpret_cast<char*>(&GamesLost_), sizeof(GamesLost_));
    for (FScore& Score : Scores_)
    {
        ScoreFile.write(reinterpret_cast<char*>(&Score), sizeof(Score));
    }
    ScoreFile.close();
}

void FPlayerScores::LoadScoreFile()
{
    if(std::filesystem::exists(ScorePath_))
    {
        std::ifstream ScoreFile;
        ScoreFile.open(ScorePath_, std::ios::in);
        ScoreFile.seekg(0);
        ScoreFile.read(reinterpret_cast<char*>(&GamesPlayed_), sizeof(GamesPlayed_));
        ScoreFile.read(reinterpret_cast<char*>(&GamesWon_), sizeof(GamesWon_));
        ScoreFile.read(reinterpret_cast<char*>(&GamesLost_), sizeof(GamesLost_));

        Scores_.clear();
        for (int i = 0; i < GamesWon_ + GamesLost_; ++i)
        {
            FScore Score;
            ScoreFile.read(reinterpret_cast<char*>(&Score), sizeof(Score));
            Scores_.push_back(Score);
        }
        ScoreFile.close();
    }
}
