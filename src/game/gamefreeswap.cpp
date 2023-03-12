#include "gamefreeswap.h"

FGameFreeSwap::FGameFreeSwap(EDifficulty Difficulty)
    :FGame{Difficulty}
{
    FGameFreeSwap::InitPuzzle();
}

void FGameFreeSwap::OnPuzzleClick(int WidgetId)
{
    if(bWin)
    {
        return;
    }

    if(PrevClickedId_ == -1)
    {
        PrevClickedId_ = WidgetId;
    }
    else
    {
        FPuzzle& PuzzleA = PuzzleVector[PrevClickedId_];
        FPuzzle& PuzzleB = PuzzleVector[WidgetId];
        if(PuzzleA.IsNeighbour(PuzzleB))
        {
            SwapPuzzlePositions(PuzzleA, PuzzleB);
            bWin = CheckWin();
        }
        PrevClickedId_ = -1;
    }
}

void FGameFreeSwap::InitPuzzle()
{
    std::vector<int> ShuffledIdx = GetShuffledIdxArray();
    for (int i = 0; i < ShuffledIdx.size(); ++i)
    {
        PuzzleVector.emplace_back(i, IndexToGridPosition(ShuffledIdx[i]), EPuzzleType::STANDARD);
    }
}
