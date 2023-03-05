#include "puzzle.h"
#include <iostream>

FPuzzle::FPuzzle(int Id, FGridPosition GridPosition)
    : Id_{Id}
    , GridPosition_{GridPosition}
{

}

const FGridPosition& FPuzzle::GridPosition() const
{
    return GridPosition_;
}

void FPuzzle::SetGridPosition(const FGridPosition &NewGridPosition)
{
    GridPosition_ = NewGridPosition;
}

void FPuzzle::SwapGridPosition(FGridPosition &NewGridPosition)
{
    std::swap(GridPosition_, NewGridPosition);
}

int FPuzzle::Id() const
{
    return Id_;
}
