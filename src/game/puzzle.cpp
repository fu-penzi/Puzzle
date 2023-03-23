#include "puzzle.h"
#include <iostream>

FPuzzle::FPuzzle()
{

}

FPuzzle::FPuzzle(int Id, FGridPosition GridPosition, EPuzzleType PuzzleType)
    : Id_{Id}
    , GridPosition_{GridPosition}
    , PuzzleType_{PuzzleType}
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

int FPuzzle::Id() const
{
    return Id_;
}

EPuzzleType FPuzzle::PuzzleType() const
{
    return PuzzleType_;
}

bool FPuzzle::IsNeighbour(const FPuzzle &Puzzle) const
{
    const FGridPosition& Position = Puzzle.GridPosition();
    const int rowDiff = abs(GridPosition_.Row - Position.Row);
    const int colDiff = abs(GridPosition_.Column - Position.Column);
    const bool bLeftRight = GridPosition_.Row == Position.Row && colDiff == 1;
    const bool bTopBottom = GridPosition_.Column == Position.Column && rowDiff == 1;

    return bLeftRight || bTopBottom;
}
