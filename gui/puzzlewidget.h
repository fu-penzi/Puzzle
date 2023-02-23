#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QPushButton>

struct FGridPosition
{
    int Row;
    int Column;
};

class FPuzzleWidget : public QPushButton
{
    Q_OBJECT

public:
    explicit FPuzzleWidget(int Id, FGridPosition GridPosition, QWidget *Parent = nullptr);

    const FGridPosition& GridPosition() const;
    void SetGridPosition(const FGridPosition &NewGridPosition);
    void SwapGridPosition(FGridPosition &NewGridPosition);

    int Id() const;

private:
    const int Id_;
    FGridPosition GridPosition_;

signals:
    void OnClick(int Id);
};
#endif // PUZZLEWIDGET_H
