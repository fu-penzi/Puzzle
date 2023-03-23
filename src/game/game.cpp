#include "game.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <random>


FGame::FGame(int GameId, EDifficulty Difficulty, EMode Mode)
    : GameState_{GameId}
    , GameConfig_{Difficulty, Mode}
{
    GameState_.Time = GameConfig_.TimeLimit();
    GameState_.PuzzleVector.reserve(GameConfig_.PuzzleNumber());
}

FGame::FGame(FGameState GameState, EDifficulty Difficulty, EMode Mode)
    : GameState_{GameState},
      GameConfig_{Difficulty, Mode}
{

}

FGame::~FGame()
{
}

int FGame::GameId() const
{
    return GameState_.GameId;
}

int FGame::Moves() const
{
    return GameState_.Moves;
}

bool FGame::bWin() const
{
    return GameState_.bWin;
}

double FGame::Time() const
{
    return GameState_.Time;
}

const std::vector<FPuzzle>& FGame::PuzzleVector() const
{
    return GameState_.PuzzleVector;
}

const FGameState& FGame::GameState() const
{
    return GameState_;
}

const FGameConfig& FGame::GameConfig() const
{
    return GameConfig_;
}

void FGame::SwapPuzzlePositions(FPuzzle& A, FPuzzle& B)
{
    ++GameState_.Moves;
    FGridPosition APosition(A.GridPosition());
    A.SetGridPosition(B.GridPosition());
    B.SetGridPosition(APosition);
}

FGridPosition FGame::IndexToGridPosition(int index)
{
    return  FGridPosition{index / GameConfig_.GridSize(), index % GameConfig_.GridSize()};
}

int FGame::GridPositionToIndex(const FGridPosition& Position)
{
    return Position.Row * GameConfig_.GridSize() + Position.Column;
}

bool FGame::CheckWin()
{
    for (const auto& Puzzle : PuzzleVector())
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
    std::vector<int> idx(GameConfig_.PuzzleNumber());
    std::iota(idx.begin(), idx.end(), 0);
    std::random_shuffle(idx.begin(),idx.end());

    return idx;
}
