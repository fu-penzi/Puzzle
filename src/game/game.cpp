#include "game.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <random>

FGame::FGame(FDifficulty Difficulty)
    : bWin{false}
{
    const int GridSize = 3;
    GameConfig = {GridSize, GridSize * GridSize - 1, 100};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, GameConfig.PuzzleNumber);
    EmptyPuzzleIndex_ = distr(gen);
    EmptyPuzzlePosition_ = {EmptyPuzzleIndex_ / GameConfig.GridSize,
                            EmptyPuzzleIndex_ % GameConfig.GridSize
                           };

    PuzzleVector.reserve(GameConfig.PuzzleNumber);
    InitPuzzle();
}

FGame::~FGame()
{
}

void FGame::InitPuzzle()
{
    std::vector<int> idx(GameConfig.PuzzleNumber);
    std::iota(idx.begin(), idx.end(), 0);
    std::random_shuffle(idx.begin(),idx.end());
    for (int i = 0; i < GameConfig.PuzzleNumber; ++i)
    {
        FPuzzle* Puzzle = new FPuzzle{i, IndexToGridPosition(idx[i])};
        PuzzleVector.emplace_back(Puzzle);
    }
}

const FGridPosition* FGame::SwapWithEmptyPuzzle(int WidgetId)
{
    if(bWin)
    {
        return nullptr;
    }
    FPuzzle* Widget = PuzzleVector[WidgetId].get();
    if(CanSwapWithEmptyPuzzle(Widget->GridPosition()))
    {
        Widget->SwapGridPosition(EmptyPuzzlePosition_);
        EmptyPuzzleIndex_ = GridPositionToIndex(EmptyPuzzlePosition_);
        Widget->SetGridPosition(Widget->GridPosition());
        bWin = CheckWin();
        return &Widget->GridPosition();
    }
    return nullptr;
}

bool FGame::CanSwapWithEmptyPuzzle(const FGridPosition &WidgetPosition)
{
    const int rowDiff = abs(WidgetPosition.Row - EmptyPuzzlePosition_.Row);
    const int colDiff = abs(WidgetPosition.Column - EmptyPuzzlePosition_.Column);
    const bool bLeftRight = WidgetPosition.Row == EmptyPuzzlePosition_.Row && colDiff == 1;
    const bool bTopBottom = WidgetPosition.Column == EmptyPuzzlePosition_.Column && rowDiff == 1;

    return bLeftRight || bTopBottom;
}

FGridPosition FGame::IndexToGridPosition(int index)
{
    return index < EmptyPuzzleIndex_ ?
           FGridPosition{index / GameConfig.GridSize,
                         index % GameConfig.GridSize} :
           FGridPosition{(index + 1) / GameConfig.GridSize,
                         (index + 1) % GameConfig.GridSize};
}

int FGame::GridPositionToIndex(const FGridPosition &Position)
{
    return Position.Row * GameConfig.GridSize + Position.Column;
}

bool FGame::CheckWin()
{
    for (const auto& Widget : PuzzleVector)
    {
        if(GridPositionToIndex(Widget.get()->GridPosition()) != Widget.get()->Id())
        {
            return false;
        }
    }
    return true;
}
