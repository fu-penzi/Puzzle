#ifndef GAMEEMPTYSWAP_H
#define GAMEEMPTYSWAP_H


#include "game.h"

class FGameEmptySwap : public FGame
{
public:
    FGameEmptySwap(EDifficulty Difficulty);

private:
    FPuzzle& GetEmptyPuzzle();

    void OnPuzzleClick(int WidgetId) override;
    void InitPuzzle() override;
};

#endif // GAMEEMPTYSWAP_H
