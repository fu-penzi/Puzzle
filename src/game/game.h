#ifndef FGAME_H
#define FGAME_H

#include "gameconfig.h"
#include "puzzle.h"

#include <vector>

/** @file */

/*! @struct FGameState
 *  @author Piotr Nowak
    @brief Represents current game state
*/
struct FGameState
{
    int GameId; /**< Game unique identifier.  */
    int Moves; /**< Number of moves player made.  */
    bool bWin; /**< If player finished game before time run out. */
    int Time; /**< Remaining time to finish game.  */
    std::vector<FPuzzle> PuzzleVector; /**< Vector of puzzles. */
};

/**
 *  @author Piotr Nowak
 *  @brief Represents game.
 */
class FGame
{

public:

    /**
     * Constructor used to make new game.
     * @param GameId game unique identifier
     * @param Difficulty game difficulty
     * @param Mode game mode
     */
    FGame(int GameId, EDifficulty Difficulty, EMode Mode);

    /**
     * Constructor used to load game from GameState
     * @param GameState
     * @param Difficulty game difficulty
     * @param Mode game mode
     */
    FGame(FGameState GameState, EDifficulty Difficulty, EMode Mode);
    virtual ~FGame();

    /**
     * Getter
     * @return Game unique identifier.
     */
    int GameId() const;

    /**
     * Getter
     * @return Number of moves player made.
     */
    int Moves() const;

    /**
     * Getter
     * @return If player finished game before time run out.
     */
    bool bWin() const;

    /**
     * Getter
     * @return Remaining time to finish game.
     */
    int Time() const;

    /**
     * Getter
     * @return  Vector of puzzles.
     */
    const std::vector<FPuzzle>& PuzzleVector() const;

    /**
     * Getter
     * @return Current game state.
     */
    const FGameState& GameState() const;

    /**
     * Getter
     * @return Config used to initialize game
     */
    const FGameConfig& GameConfig() const;

public:
    /**
     * Pure virtual function used to handle player clicking puzzle
     * @param WidgetId id of puzzle clicked
     */
    virtual void OnPuzzleClick(int WidgetId) = 0;

    /**
     * Decrement remaining time
     */
    void UpdateTimer();

    /**
     * Check if game is finished
     * @return is game finished
     */
    bool IsFinished();

protected:
    FGameState GameState_{};
    FGameConfig GameConfig_{};

protected:
    bool CheckWin();
    void SwapPuzzlePositions(FPuzzle& A, FPuzzle& B);
    FGridPosition IndexToGridPosition(int index);
    std::vector<int> GetShuffledIdxArray();
    virtual void InitPuzzle() = 0;

private:
    int GridPositionToIndex(const FGridPosition& Position);
};

#endif // FGAME_H
