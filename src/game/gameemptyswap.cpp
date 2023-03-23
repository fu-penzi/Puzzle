#include "gameemptyswap.h"

FGameEmptySwap::FGameEmptySwap(int GameId, EDifficulty Difficulty, EMode Mode)
    :FGame{GameId, Difficulty, Mode}
{
    FGameEmptySwap::InitPuzzle();
}

FGameEmptySwap::FGameEmptySwap(FGameState GameState, EDifficulty Difficulty, EMode Mode)
    :FGame{GameState, Difficulty, Mode}
{

}

FPuzzle& FGameEmptySwap::GetEmptyPuzzle()
{
    return GameState_.PuzzleVector[GameConfig_.PuzzleNumber() - 1];
}

void FGameEmptySwap::OnPuzzleClick(int WidgetId)
{
    if(GameState_.bWin)
    {
        return;
    }

    FPuzzle& Puzzle = GameState_.PuzzleVector[WidgetId];
    if(GetEmptyPuzzle().IsNeighbour(Puzzle))
    {
        SwapPuzzlePositions(Puzzle, GetEmptyPuzzle());
        GameState_.bWin = CheckWin();
    }
}

void FGameEmptySwap::InitPuzzle()
{
    std::vector<int> ShuffledIdx = GetShuffledIdxArray();
    for (int i = 0; i < ShuffledIdx.size() - 1; ++i)
    {
        GameState_.PuzzleVector.emplace_back(i, IndexToGridPosition(ShuffledIdx[i]), EPuzzleType::STANDARD);
    }
    GameState_.PuzzleVector.emplace_back(ShuffledIdx.size() - 1, IndexToGridPosition(ShuffledIdx.back()), EPuzzleType::EMPTY);
}
