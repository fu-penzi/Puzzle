#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windialog.h"

#include <QGridLayout>
#include <QPalette>
#include <iostream>

MainWindow::MainWindow(QWidget *Parent)
    : QMainWindow(Parent)
    , Ui_{new Ui::MainWindow}
, PuzzleGrid_{}
, Difficulty{FDifficulty::Default}
{
    Ui_->setupUi(this);

    QPixmap Bkgnd(":/bg.png");
    Bkgnd = Bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette Palette;
    Palette.setBrush(QPalette::Window, Bkgnd);
    setPalette(Palette);

    PuzzleGrid_ = findChild<QObject*>("puzzle")->findChild<QGridLayout *>("gridLayout");

    InitActions();
}

MainWindow::~MainWindow()
{
    delete Ui_;
}

void MainWindow::InitActions()
{
    QMenuBar* MenuBar = findChild<QMenuBar*>("menubar");
    QMenu* GameMenu = MenuBar->findChild<QMenu *>("game");
    QMenu* DifficultyMenu = MenuBar->findChild<QMenu *>("difficulty");

    NewGame_ = new QAction("New game", GameMenu);
    connect(NewGame_, &QAction::triggered, this, [&]()
    {
        NewGame(Difficulty);
    });
    GameMenu->addAction(NewGame_);

    DifficultyActions_ = new QActionGroup(DifficultyMenu);
    DifficultyActions_->setExclusive(true);

    auto InitDifficultyAction = [&](QAction* Action, QString Name, FDifficulty ActionDifficulty)
    {
        Action = new QAction(Name, DifficultyActions_);
        Action->setCheckable(true);
        connect(Action, &QAction::triggered, this, [&, ActionDifficulty]()
        {
            NewGame(ActionDifficulty);
            Difficulty = ActionDifficulty;
        });

        DifficultyMenu->addAction(Action);
        DifficultyActions_->addAction(Action);

        if(ActionDifficulty == FDifficulty::Default)
        {
            Action->setChecked(true);
            Action->trigger();
        }
    };

    InitDifficultyAction(Easy_, "Easy", FDifficulty::Easy);
    InitDifficultyAction(Medium_, "Medium", FDifficulty::Medium);
    InitDifficultyAction(Hard_, "Hard", FDifficulty::Hard);
}

void MainWindow::InitPuzzleWidgets()
{
    for (auto& Puzzle: Game_.get()->PuzzleVector)
    {
        auto Widget = std::make_shared<FPuzzleWidget>(Puzzle.Id());
        PuzzleWidgets_.push_back(Widget);
        UpdateGridPosition(Widget.get(), Puzzle.GridPosition());
        connect(Widget.get(), &FPuzzleWidget::OnClick, this, &MainWindow::SwapWithEmptyPuzzle);
    }
}

void MainWindow::NewGame(FDifficulty Difficulty)
{
    Game_ = std::make_unique<FGame>(Difficulty);
    PuzzleWidgets_.clear();
    PuzzleWidgets_.reserve(Game_.get()->GameConfig.PuzzleNumber());
    InitPuzzleWidgets();
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
    auto GridPos = Game_.get()->SwapWithEmptyPuzzle(WidgetId);
    if(GridPos != nullptr)
    {
        UpdateGridPosition(Widget, *GridPos);
    }

    if(Game_.get()->bWin)
    {
        ShowWinDialog();
    }
}

void MainWindow::ShowWinDialog()
{
    WinDialog_.show();
}
