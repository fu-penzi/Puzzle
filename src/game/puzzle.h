#ifndef PUZZLE_H
#define PUZZLE_H


struct FGridPosition
{
    int Row;
    int Column;
};

class FPuzzle
{
public:
    FPuzzle(int Id, FGridPosition GridPosition);

    const FGridPosition& GridPosition() const;
    void SetGridPosition(const FGridPosition &NewGridPosition);
    void SwapGridPosition(FGridPosition &NewGridPosition);

    int Id() const;

private:
    const int Id_;
    FGridPosition GridPosition_;
};

#endif // PUZZLE_H
