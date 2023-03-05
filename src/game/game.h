#ifndef FGAME_H
#define FGAME_H

#include "puzzle.h"

#include <memory>
#include <vector>

enum class FDifficulty
{
    Easy,
    Medium,
    Hard
};

struct FGameConfig
{
    int GridSize;
    int PuzzleNumber;
    double TimeLimit;
};

typedef std::vector<std::unique_ptr<FPuzzle>> FPuzzleVector;

class FGame
{

public:
    int Score;
    double Time;
    bool bWin;
    FGameConfig GameConfig;
    FPuzzleVector PuzzleVector;

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
