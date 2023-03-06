#ifndef FGAME_H
#define FGAME_H

#include "gameconfig.h"
#include "puzzle.h"

#include <memory>
#include <vector>

class FGame
{

public:
    int Score;
    double Time;
    bool bWin;
    FGameConfig GameConfig;
    std::vector<FPuzzle> PuzzleVector;

private:
    FGridPosition EmptyPuzzlePosition_;
    int EmptyPuzzleIndex_;


public:
    FGame(FDifficulty Difficulty);
    ~FGame();

    const FGridPosition* SwapWithEmptyPuzzle(int WidgetId);

private:
    void InitPuzzle();
    void ShufflePuzzleWidgets();
    bool CanSwapWithEmptyPuzzle(const FGridPosition& Position);
    FGridPosition IndexToGridPosition(int index);
    int GridPositionToIndex(const FGridPosition& Position);
    bool CheckWin();
};

#endif // FGAME_H
