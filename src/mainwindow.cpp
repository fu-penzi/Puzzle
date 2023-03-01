#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windialog.h"

#include <QGridLayout>

#include <iostream>

MainWindow::MainWindow(QWidget *Parent)
    : QMainWindow(Parent)
    , Ui_{new Ui::MainWindow}
, PuzzleGrid_{}
, EmptyPuzzleIndex{3}
, EmptyPuzzlePosition_{EmptyPuzzleIndex / GridSize, EmptyPuzzleIndex % GridSize }
{
    Ui_->setupUi(this);
    PuzzleGrid_ = findChild<QObject*>("puzzle")->findChild<QGridLayout *>("gridLayout");
    PuzzleWidgets_.reserve(PuzzleNumber);
    InitPuzzleWidgets();
}

MainWindow::~MainWindow()
{
    delete Ui_;
}

void MainWindow::InitPuzzleWidgets()
{
    for (int i = 0; i < PuzzleNumber; ++i)
    {
        FGridPosition GridPosition = IndexToGridPosition(i);
        FPuzzleWidget* Widget = new FPuzzleWidget{i, GridPosition};
        PuzzleWidgets_.emplace_back(Widget);
        UpdateGridPosition(Widget, GridPosition);
        connect(Widget, &FPuzzleWidget::OnClick, this, &MainWindow::SwapWithEmptyPuzzle);
    }
    ShufflePuzzleWidgets();
}

void MainWindow::UpdateGridPosition(FPuzzleWidget* Widget, const FGridPosition &Position)
{
    Widget->SetGridPosition(Position);
    if(PuzzleGrid_->itemAtPosition(Position.Row, Position.Column))
    {
        PuzzleGrid_->removeWidget(Widget);
    }
    PuzzleGrid_->addWidget(Widget, Position.Row, Position.Column);
}

void MainWindow::ShufflePuzzleWidgets()
{
    std::vector<int> idx(PuzzleNumber);
    std::iota(idx.begin(), idx.end(), 0);
    std::random_shuffle(idx.begin(),idx.end());
    for (int i = 0; i < PuzzleNumber; ++i)
    {
        UpdateGridPosition(PuzzleWidgets_[i].get(), IndexToGridPosition(idx[i]));
    }
}

void MainWindow::SwapWithEmptyPuzzle(int WidgetId)
{
    if(bWin)
    {
        return;
    }
    FPuzzleWidget* Widget = PuzzleWidgets_[WidgetId].get();
    if(CanSwapWithEmptyPuzzle(Widget->GridPosition()))
    {
        Widget->SwapGridPosition(EmptyPuzzlePosition_);
        EmptyPuzzleIndex = GridPositionToIndex(EmptyPuzzlePosition_);
        UpdateGridPosition(Widget, Widget->GridPosition());
    }
    bWin = CheckWin();
}

bool MainWindow::CanSwapWithEmptyPuzzle(const FGridPosition &WidgetPosition)
{
    const int rowDiff = abs(WidgetPosition.Row - EmptyPuzzlePosition_.Row);
    const int colDiff = abs(WidgetPosition.Column - EmptyPuzzlePosition_.Column);
    const bool bLeftRight = WidgetPosition.Row == EmptyPuzzlePosition_.Row && colDiff == 1;
    const bool bTopBottom = WidgetPosition.Column == EmptyPuzzlePosition_.Column && rowDiff == 1;

    return bLeftRight || bTopBottom;
}

FGridPosition MainWindow::IndexToGridPosition(int index)
{
    return index < EmptyPuzzleIndex ?
           FGridPosition{index / GridSize, index % GridSize} :
           FGridPosition{(index + 1) / GridSize, (index + 1) % GridSize};
}

int MainWindow::GridPositionToIndex(const FGridPosition &Position)
{
    return Position.Row * GridSize + Position.Column;
}

bool MainWindow::CheckWin()
{
    for (auto& Widget : PuzzleWidgets_)
    {
        if(GridPositionToIndex(Widget.get()->GridPosition()) != Widget.get()->Id())
        {
            return false;
        }
    }
    FWinDialog* WinDialog =  new FWinDialog();
    WinDialog->show();
    return true;
}
