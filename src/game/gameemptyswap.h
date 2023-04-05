#ifndef GAMEEMPTYSWAP_H
#define GAMEEMPTYSWAP_H


#include "game.h"

class FGameEmptySwap : public FGame
{

public:
    FGameEmptySwap(int GameId, EDifficulty Difficulty, EMode Mode);
    FGameEmptySwap(FGameState GameState, EDifficulty Difficulty, EMode Mode);

private:
    FPuzzle& GetEmptyPuzzle();

    void OnPuzzleClick(int WidgetId) override;
    void InitPuzzle() override;
};

#endif // GAMEEMPTYSWAP_H
