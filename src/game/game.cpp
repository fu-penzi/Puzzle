#include "game.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <random>

FGame::FGame(EDifficulty Difficulty)
    : bWin{false}
    , GameConfig{Difficulty}
{
    PuzzleVector.reserve(GameConfig.PuzzleNumber());
}

FGame::~FGame()
{
}

void FGame::SwapPuzzlePositions(FPuzzle& A, FPuzzle& B)
{
    FGridPosition APosition(A.GridPosition());
    A.SetGridPosition(B.GridPosition());
    B.SetGridPosition(APosition);
}

FGridPosition FGame::IndexToGridPosition(int index)
{
    return  FGridPosition{index / GameConfig.GridSize(), index % GameConfig.GridSize()};
}

int FGame::GridPositionToIndex(const FGridPosition& Position)
{
    return Position.Row * GameConfig.GridSize() + Position.Column;
}

bool FGame::CheckWin()
{
    for (const auto& Puzzle : PuzzleVector)
    {
        if(GridPositionToIndex(Puzzle.GridPosition()) != Puzzle.Id())
        {
            return false;
        }
    }
    return true;
}

std::vector<int> FGame::GetShuffledIdxArray()
{
    std::vector<int> idx(GameConfig.PuzzleNumber());
    std::iota(idx.begin(), idx.end(), 0);
    std::random_shuffle(idx.begin(),idx.end());

    return idx;
}
