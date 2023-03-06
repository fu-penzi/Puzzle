#include "gameconfig.h"

FGameConfig::FGameConfig(FDifficulty Difficulty):
    Difficulty_{Difficulty}
{
    switch (Difficulty)
    {
    case FDifficulty::Easy:
        GridSize_ = 3;
        TimeLimit_ = 120;
        break;
    case FDifficulty::Medium:
        GridSize_ = 4;
        TimeLimit_ = 180;
        break;
    case FDifficulty::Hard:
        GridSize_ = 5;
        TimeLimit_ = 240;
        break;
    default:
        GridSize_ = 3;
        TimeLimit_ = 120;
        break;
    }
    PuzzleNumber_ = GridSize_ * GridSize_ - 1;
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

FDifficulty FGameConfig::Difficulty() const
{
    return Difficulty_;
}
