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
    FPuzzle();
    FPuzzle(int Id, FGridPosition GridPosition, EPuzzleType PuzzleType);
    FGridPosition GridPosition_{};

    const FGridPosition& GridPosition() const;
    void SetGridPosition(const FGridPosition &NewGridPosition);
    int Id() const;
    EPuzzleType PuzzleType() const;

    bool IsNeighbour(const FPuzzle &Puzzle) const;

private:
    const int Id_{};
    const EPuzzleType PuzzleType_{};

};

#endif // PUZZLE_H
