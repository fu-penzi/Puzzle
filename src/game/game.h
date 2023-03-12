#ifndef FGAME_H
#define FGAME_H

#include "gameconfig.h"
#include "puzzle.h"

#include <vector>

class FGame
{

public:
    bool bWin;
    FGameConfig GameConfig;
    std::vector<FPuzzle> PuzzleVector;

public:
    FGame(EDifficulty Difficulty);
    virtual ~FGame();

    virtual void OnPuzzleClick(int WidgetId) = 0;

protected:
    void SwapPuzzlePositions(FPuzzle& A, FPuzzle& B);
    FGridPosition IndexToGridPosition(int index);
    bool CheckWin();
    std::vector<int> GetShuffledIdxArray();

    virtual void InitPuzzle() = 0;

private:
    int GridPositionToIndex(const FGridPosition& Position);
};

#endif // FGAME_H
