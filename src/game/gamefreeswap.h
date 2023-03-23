#ifndef GAMEFREESWAP_H
#define GAMEFREESWAP_H


#include "game.h"

class FGameFreeSwap : public FGame
{
public:
    FGameFreeSwap(int GameId, EDifficulty Difficulty, EMode Mode);
    FGameFreeSwap(FGameState GameState, EDifficulty Difficulty, EMode Mode);

private:
    int PrevClickedId_{-1};

    void OnPuzzleClick(int WidgetId) override;
    void InitPuzzle() override;
};

#endif // GAMEFREESWAP_H