#ifndef GAMEFREESWAP_H
#define GAMEFREESWAP_H


#include "game.h"

/**
 *  @author Piotr Nowak
 *  @brief Represents variant of game without empty grid space and with free puzzle swapping.
 */
class FGameFreeSwap : public FGame
{

public:
    /**
     * Constructor used to make new game.
     * @param GameId game unique identifier
     * @param Difficulty game difficulty
     * @param Mode game mode
     */
    FGameFreeSwap(int GameId, EDifficulty Difficulty, EMode Mode);

    /**
     * Constructor used to load game from GameState
     * @param GameState
     * @param Difficulty game difficulty
     * @param Mode game mode
     */
    FGameFreeSwap(FGameState GameState, EDifficulty Difficulty, EMode Mode);

public:
    /**
     * Handle player clicking puzzle
     * @param WidgetId id of puzzle clicked
     */
    void OnPuzzleClick(int WidgetId) override;

private:
    int PrevClickedId_{-1};

private:
    void InitPuzzle() override;
};

#endif // GAMEFREESWAP_H
