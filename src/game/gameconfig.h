#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <map>
#include <string>

/** @file */

/*! @enum EMode
 *  @author Piotr Nowak
 *  @brief An enum class describing game mode.
*/
enum class EMode
{
    FreeSwap, /**< Variant of game without empty grid space and with free puzzle swapping.  */
    EmptySwap, /**< Variant of game with one empty grid space. */
    Default = EmptySwap /**< Default game mode (EmptySwap).  */
};

/*! @enum EDifficulty
 *  @author Piotr Nowak
 *  @brief An enum class describing game difficulty. Has impact on time to finish game and grid size.
*/
enum class EDifficulty
{
    Easy, /**< Easy game mode.  */
    Medium, /**< Medium game mode.   */
    Hard, /**< Hard game mode.  */
    Default = Easy /**< Default game mode (Easy).  */
};

template <size_t N>
using TStringArray =  std::array<const std::string_view, N>;

/**
 *  @author Piotr Nowak
 *  @brief Represents a single puzzle piece.
 */
class FGameConfig
{
public:

    /**
    * Default constructor
    */
    FGameConfig();

    /**
    * Constructor used to initialize config values.
    * @param Difficulty
    * @param Mode
    */
    FGameConfig(EDifficulty Difficulty, EMode Mode);


    /**
    * Getter
    * @return Length of one side of puzzle grid.
    */
    int GridSize() const;

    /**
    * Getter
    * @return Total number of puzzle in grid.
    */
    int PuzzleNumber() const;

    /**
    * Getter
    * @return Time limit of game.
    */
    double TimeLimit() const;

    /**
    * Getter
    * @return Game difficulty.
    */
    EDifficulty Difficulty() const;

    /**
    * Getter
    * @return Game mode.
    */
    EMode Mode() const;

public:

    /**
    * Convert EMode value to string.
    * @param Mode to convert to string.
    * @return Stringified game mode.
    */
    static std::string ModeToString(EMode Mode)
    {
        return std::string{ModeStrings_[static_cast<int>(Mode)]};
    }

    /**
    * Convert EDifficulty value to string.
    * @param Difficulty to convert to string.
    * @return Stringified difficulty.
    */
    static std::string DifficultyToString(EDifficulty Difficulty)
    {
        return std::string{DifficultyStrings_[static_cast<int>(Difficulty)]};
    }

private:
    int GridSize_;
    int PuzzleNumber_;
    double TimeLimit_;
    EDifficulty Difficulty_;
    EMode Mode_;

    constexpr static TStringArray<2> ModeStrings_ { "Free swap", "Empty tile swapping" };
    constexpr static TStringArray<3> DifficultyStrings_ { "Easy", "Medium", "Hard" };

};

#endif // GAMECONFIG_H
