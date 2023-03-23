#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <map>
#include <string>

enum class EMode
{
    FreeSwap,
    EmptySwap,
    Default = EmptySwap
};

enum class EDifficulty
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
    EDifficulty Difficulty_;
    EMode Mode_;

public:
    FGameConfig();
    FGameConfig(EDifficulty Difficulty, EMode Mode);

    int GridSize() const;
    int PuzzleNumber() const;
    double TimeLimit() const;
    EDifficulty Difficulty() const;
    EMode Mode() const;
};

#endif // GAMECONFIG_H
