#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windialog.h"

#include <QGridLayout>
#include <QPalette>
#include <iostream>

MainWindow::MainWindow(QWidget *Parent)
    : QMainWindow(Parent)
    , Game_{FDifficulty::Easy}
    , Ui_{new Ui::MainWindow}
, PuzzleGrid_{}
{
    Ui_->setupUi(this);
    QPixmap Bkgnd(":/bg.png");
    Bkgnd = Bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette Palette;
    Palette.setBrush(QPalette::Window, Bkgnd);
    setPalette(Palette);

    PuzzleGrid_ = findChild<QObject*>("puzzle")->findChild<QGridLayout *>("gridLayout");
    NewGame(FDifficulty::Easy);
}

MainWindow::~MainWindow()
{
    delete Ui_;
}

void MainWindow::NewGame(FDifficulty Difficulty)
{
//    Game_ = FGame{Difficulty};
    InitPuzzleWidgets();
    PuzzleWidgets_.reserve(Game_.GameConfig.PuzzleNumber);
}

void MainWindow::InitPuzzleWidgets()
{
    for (auto& Puzzle: Game_.PuzzleVector)
    {
        FPuzzleWidget* Widget = new FPuzzleWidget{Puzzle.get()->Id()};
        PuzzleWidgets_.emplace_back(Widget);
        UpdateGridPosition(Widget, Puzzle.get()->GridPosition());
        connect(Widget, &FPuzzleWidget::OnClick, this, &MainWindow::SwapWithEmptyPuzzle);
    }
}

void MainWindow::UpdateGridPosition(FPuzzleWidget* Widget, const FGridPosition &Position)
{
    if(PuzzleGrid_->itemAtPosition(Position.Row, Position.Column))
    {
        PuzzleGrid_->removeWidget(Widget);
    }
    PuzzleGrid_->addWidget(Widget, Position.Row, Position.Column);
}

void MainWindow::SwapWithEmptyPuzzle(int WidgetId)
{
    FPuzzleWidget* Widget = PuzzleWidgets_[WidgetId].get();
    auto GridPos = Game_.SwapWithEmptyPuzzle(WidgetId);
    if(GridPos != nullptr)
    {
        UpdateGridPosition(Widget, *GridPos);
    }

    if(Game_.bWin)
    {
        FWinDialog* WinDialog =  new FWinDialog();
        WinDialog->show();
    }
}

void MainWindow::ShowWinDialog()
{
    FWinDialog* WinDialog =  new FWinDialog();
    WinDialog->show();
}
