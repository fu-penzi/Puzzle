#ifndef PUZZLE_H
#define PUZZLE_H


struct FGridPosition
{
    int Row;
    int Column;
};

enum class EPuzzleType
{
    STANDARD,
    EMPTY
};

class FPuzzle
{
public:
    const FGridPosition& GridPosition() const;
    void SetGridPosition(const FGridPosition &NewGridPosition);
    int Id() const;
    EPuzzleType PuzzleType() const;

private:
    FGridPosition GridPosition_{};
    const int Id_{};
    const EPuzzleType PuzzleType_{};

public:
    FPuzzle();
    FPuzzle(int Id, FGridPosition GridPosition, EPuzzleType PuzzleType);

    bool IsNeighbour(const FPuzzle &Puzzle) const;
};

#endif // PUZZLE_H
