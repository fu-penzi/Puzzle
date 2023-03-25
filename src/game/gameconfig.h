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
public:

private:
    int GridSize_;
    int PuzzleNumber_;
    double TimeLimit_;
    EDifficulty Difficulty_;
    EMode Mode_;

    constexpr static std::array<const std::string_view, 2> ModeStrings_ { "Free swap", "Empty tile swapping" };
    constexpr static std::array<const std::string_view, 3> DifficultyStrings_ { "Easy", "Medium", "Hard" };

public:
    FGameConfig();
    FGameConfig(EDifficulty Difficulty, EMode Mode);

    int GridSize() const;
    int PuzzleNumber() const;
    double TimeLimit() const;
    EDifficulty Difficulty() const;
    EMode Mode() const;

    static std::string ModeToString(EMode Mode)
    {
        return std::string{ModeStrings_[static_cast<int>(Mode)]};
    }

    static std::string DifficultyToString(EDifficulty Difficulty)
    {
        return std::string{DifficultyStrings_[static_cast<int>(Difficulty)]};
    }
};

#endif // GAMECONFIG_H
