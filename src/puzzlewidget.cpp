#include "puzzlewidget.h"

#include <QPushButton>
#include <QString>
#include <iostream>

FPuzzleWidget::FPuzzleWidget(int Id, FGridPosition GridPosition, QWidget *Parent)
    : QPushButton{*new QString(std::to_string(Id).c_str()), Parent}
    , Id_{Id}
    , GridPosition_{GridPosition}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(this, &QPushButton::clicked, this, [&]()
    {
        emit OnClick(Id_);
    });
}

const FGridPosition& FPuzzleWidget::GridPosition() const
{
    return GridPosition_;
}

void FPuzzleWidget::SetGridPosition(const FGridPosition &NewGridPosition)
{
    GridPosition_ = NewGridPosition;
}

void FPuzzleWidget::SwapGridPosition(FGridPosition &NewGridPosition)
{
    std::swap(GridPosition_, NewGridPosition);
}

int FPuzzleWidget::Id() const
{
    return Id_;
}
