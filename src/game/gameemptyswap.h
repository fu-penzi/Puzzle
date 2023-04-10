#ifndef GAMEEMPTYSWAP_H
#define GAMEEMPTYSWAP_H


#include "game.h"

/**
 *  @author Piotr Nowak
 *  @brief Represents variant of game with one empty grid space.
 */
class FGameEmptySwap : public FGame
{

public:

    /**
     * Constructor used to make new game.
     * @param GameId game unique identifier
     * @param Difficulty game difficulty
     * @param Mode game mode
     */
    FGameEmptySwap(int GameId, EDifficulty Difficulty, EMode Mode);

    /**
     * Constructor used to load game from GameState
     * @param GameState
     * @param Difficulty game difficulty
     * @param Mode game mode
     */
    FGameEmptySwap(FGameState GameState, EDifficulty Difficulty, EMode Mode);

public:
    /**
     * Handle player clicking puzzle
     * @param WidgetId id of puzzle clicked
     */
    void OnPuzzleClick(int WidgetId) override;

private:
    FPuzzle& GetEmptyPuzzle();
    void InitPuzzle() override;
};

#endif // GAMEEMPTYSWAP_H
