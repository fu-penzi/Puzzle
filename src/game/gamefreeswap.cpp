#include "gamefreeswap.h"

FGameFreeSwap::FGameFreeSwap(int GameId, EDifficulty Difficulty, EMode Mode)
    :FGame{GameId, Difficulty, Mode}
{
    FGameFreeSwap::InitPuzzle();
}

FGameFreeSwap::FGameFreeSwap(FGameState GameState, EDifficulty Difficulty, EMode Mode)
    :FGame{GameState, Difficulty, Mode}
{

}

void FGameFreeSwap::OnPuzzleClick(int WidgetId)
{
    if(GameState_.bWin)
    {
        return;
    }

    if(PrevClickedId_ == -1)
    {
        PrevClickedId_ = WidgetId;
    }
    else
    {
        FPuzzle& PuzzleA = GameState_.PuzzleVector[PrevClickedId_];
        FPuzzle& PuzzleB = GameState_.PuzzleVector[WidgetId];
        if(PuzzleA.IsNeighbour(PuzzleB))
        {
            SwapPuzzlePositions(PuzzleA, PuzzleB);
            GameState_.bWin = CheckWin();
        }
        PrevClickedId_ = -1;
    }
}

void FGameFreeSwap::InitPuzzle()
{
    std::vector<int> ShuffledIdx = GetShuffledIdxArray();
    for (int i = 0; i < ShuffledIdx.size(); ++i)
    {
        GameState_.PuzzleVector.emplace_back(i, IndexToGridPosition(ShuffledIdx[i]), EPuzzleType::STANDARD);
    }
}
