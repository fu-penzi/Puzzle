#include "gameemptyswap.h"

FGameEmptySwap::FGameEmptySwap(EDifficulty Difficulty)
    :FGame{Difficulty}
{
    FGameEmptySwap::InitPuzzle();
}

FPuzzle &FGameEmptySwap::GetEmptyPuzzle()
{
    return PuzzleVector[GameConfig.PuzzleNumber() - 1];
}


void FGameEmptySwap::OnPuzzleClick(int WidgetId)
{
    if(bWin)
    {
        return;
    }

    FPuzzle& Puzzle = PuzzleVector[WidgetId];
    if(GetEmptyPuzzle().IsNeighbour(Puzzle))
    {
        SwapPuzzlePositions(Puzzle, GetEmptyPuzzle());
        bWin = CheckWin();
    }
}

void FGameEmptySwap::InitPuzzle()
{
    std::vector<int> ShuffledIdx = GetShuffledIdxArray();
    for (int i = 0; i < ShuffledIdx.size() - 1; ++i)
    {
        PuzzleVector.emplace_back(i, IndexToGridPosition(ShuffledIdx[i]), EPuzzleType::STANDARD);
    }
    PuzzleVector.emplace_back(ShuffledIdx.size() - 1, IndexToGridPosition(ShuffledIdx.back()), EPuzzleType::EMPTY);
}
