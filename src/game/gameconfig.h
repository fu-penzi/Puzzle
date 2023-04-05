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

template <size_t N>
using FStringArray =  std::array<const std::string_view, N>;

class FGameConfig
{
public:
    int GridSize() const;
    int PuzzleNumber() const;
    double TimeLimit() const;
    EDifficulty Difficulty() const;
    EMode Mode() const;

private:
    int GridSize_;
    int PuzzleNumber_;
    double TimeLimit_;
    EDifficulty Difficulty_;
    EMode Mode_;
    constexpr static FStringArray<2> ModeStrings_ { "Free swap", "Empty tile swapping" };
    constexpr static FStringArray<3> DifficultyStrings_ { "Easy", "Medium", "Hard" };

public:
    FGameConfig();
    FGameConfig(EDifficulty Difficulty, EMode Mode);

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
