#include "gameconfig.h"

FGameConfig::FGameConfig()
{

}

FGameConfig::FGameConfig(EDifficulty Difficulty, EMode Mode):
    Difficulty_{Difficulty}
    , Mode_{Mode}
{
    switch (Difficulty)
    {
    case EDifficulty::Easy:
        GridSize_ = 2;
        TimeLimit_ = 120;
        break;
    case EDifficulty::Medium:
        GridSize_ = 4;
        TimeLimit_ = 180;
        break;
    case EDifficulty::Hard:
        GridSize_ = 5;
        TimeLimit_ = 240;
        break;
    default:
        GridSize_ = 3;
        TimeLimit_ = 120;
        break;
    }
    PuzzleNumber_ = GridSize_ * GridSize_;
}

int FGameConfig::PuzzleNumber() const
{
    return PuzzleNumber_;
}

double FGameConfig::TimeLimit() const
{
    return TimeLimit_;
}

int FGameConfig::GridSize() const
{
    return GridSize_;
}

EDifficulty FGameConfig::Difficulty() const
{
    return Difficulty_;
}


EMode FGameConfig::Mode() const
{
    return Mode_;
}
