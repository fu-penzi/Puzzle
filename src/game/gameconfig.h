#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <map>
#include <string>

enum class FDifficulty
{
    Easy,
    Medium,
    Hard,
    Default = Easy
};

class FGameConfig
{
private:
    int GridSize_;
    int PuzzleNumber_;
    double TimeLimit_;
    FDifficulty Difficulty_;

public:
    FGameConfig(FDifficulty Difficulty);

    int GridSize() const;
    int PuzzleNumber() const;
    double TimeLimit() const;
    FDifficulty Difficulty() const;
};

#endif // GAMECONFIG_H
