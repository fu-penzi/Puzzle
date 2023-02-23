#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

#include <iostream>

MainWindow::MainWindow(QWidget *Parent)
    : QMainWindow(Parent)
    , Ui_{new Ui::MainWindow}, PuzzleGrid_{}, EmptyPuzzlePosition_{0, 3}
{
    Ui_->setupUi(this);
    PuzzleGrid_ = findChild<QObject*>("puzzle")->findChild<QGridLayout *>("gridLayout");
    initPuzzleWidgets();
}

MainWindow::~MainWindow()
{
    delete Ui_;
}

void MainWindow::initPuzzleWidgets()
{
    PuzzleWidgets_.reserve(PuzzleNumber);
    const int EmptyPuzzleIndex = EmptyPuzzlePosition_.Row * GridSize + EmptyPuzzlePosition_.Column;
    for (int i = 0; i < PuzzleNumber; ++i)
    {
        FGridPosition GridPosition = i < EmptyPuzzleIndex ?
                                     FGridPosition{i / GridSize, i % GridSize} :
                                     FGridPosition{(i+1) / GridSize, (i+1) % GridSize};
        FPuzzleWidget* PuzzleWidget = new FPuzzleWidget{i, GridPosition};
        PuzzleWidgets_.emplace_back(PuzzleWidget);
        PuzzleGrid_->addWidget(PuzzleWidget,
                               PuzzleWidget->GridPosition().Row,
                               PuzzleWidget->GridPosition().Column);
        connect(PuzzleWidget, &FPuzzleWidget::OnClick, this, &MainWindow::SwapWithEmptyPuzzle);
    }
}

void MainWindow::SwapWithEmptyPuzzle(int WidgetId)
{
    FPuzzleWidget* Widget = PuzzleWidgets_[WidgetId].get();
    if(CanSwapWithEmptyPuzzle(Widget->GridPosition()))
    {
        Widget->SwapGridPosition(EmptyPuzzlePosition_);
        PuzzleGrid_->removeWidget(Widget);
        PuzzleGrid_->addWidget(Widget,
                               Widget->GridPosition().Row,
                               Widget->GridPosition().Column);
    }
}

bool MainWindow::CanSwapWithEmptyPuzzle(const FGridPosition &WidgetPosition)
{
    const int rowDiff = abs(WidgetPosition.Row - EmptyPuzzlePosition_.Row);
    const int colDiff = abs(WidgetPosition.Column - EmptyPuzzlePosition_.Column);
    const bool bLeftRight = WidgetPosition.Row == EmptyPuzzlePosition_.Row && colDiff == 1;
    const bool bTopBottom = WidgetPosition.Column == EmptyPuzzlePosition_.Column && rowDiff == 1;

    return bLeftRight || bTopBottom;
}
