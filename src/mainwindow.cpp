#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windialog.h"

#include <QGridLayout>
#include <QPalette>
#include <iostream>

MainWindow::MainWindow(QWidget *Parent)
    : QMainWindow(Parent)
    , Ui_{new Ui::MainWindow}
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
    QMenu* GameMenu = MenuBar->findChild<QMenu*>("game");
    QMenu* DifficultyMenu = MenuBar->findChild<QMenu*>("difficulty");
    QMenu* GameModeMenu = MenuBar->findChild<QMenu*>("gameMode");

    NewGame_.setParent(GameMenu);
    connect(&NewGame_, &QAction::triggered, this, [&]()
    {
        NewGame();
    });
    GameMenu->addAction(&NewGame_);

    const QList<QAction*> DifficultyActionList = {&Easy_, &Medium_, &Hard_};
    constexpr std::array<EDifficulty, 3> Difficulties{EDifficulty::Easy, EDifficulty::Medium, EDifficulty::Hard};
    InitActionsHandler(DifficultyActionList, Difficulties, Difficulty);
    InitActionGroup(DifficultyActionList, DifficultyMenu, DifficultyActionGroup_);

    const QList<QAction*> GameActionList = {&FreeSwap_, &EmptySwap_};
    constexpr std::array<EMode, 2> Modes{EMode::FreeSwap, EMode::EmptySwap};
    InitActionsHandler(GameActionList, Modes, GameMode);
    InitActionGroup(GameActionList, GameModeMenu, GameModeActionGroup_);

    NewGame();
}

void MainWindow::InitActionGroup(QList<QAction*> Actions, QMenu* Menu, QActionGroup& ActionGroup)
{
    ActionGroup.setParent(Menu);
    ActionGroup.setExclusive(true);
    Menu->addActions(Actions);
    for (auto& Action : Actions)
    {
        ActionGroup.addAction(Action);
        Action->setCheckable(true);
    }
}

void MainWindow::InitPuzzleWidgets()
{
    for (auto& Puzzle: Player_.CurrentGame.get()->PuzzleVector)
    {
        if(Puzzle.PuzzleType() == EPuzzleType::EMPTY)
        {
            continue;
        }
        auto Widget = std::make_shared<FPuzzleWidget>(Puzzle.Id());
        PuzzleWidgets_.push_back(Widget);
        connect(Widget.get(), &FPuzzleWidget::OnClick, this, &MainWindow::SwapWithEmptyPuzzle);
    }
    UpdateGrid();
}

void MainWindow::NewGame()
{
    Player_.NewGame(Difficulty, GameMode);
    PuzzleWidgets_.clear();
    PuzzleWidgets_.reserve(Player_.CurrentGame.get()->GameConfig.PuzzleNumber());
    InitPuzzleWidgets();
}

void MainWindow::UpdateGrid()
{
    auto PuzzleVector = Player_.CurrentGame.get()->PuzzleVector;
    for(int i = 0; i < PuzzleVector.size(); ++i)
    {
        if(PuzzleVector[i].PuzzleType() == EPuzzleType::EMPTY)
        {
            continue;
        }
        UpdateGridPosition(PuzzleWidgets_[i].get(), PuzzleVector[i].GridPosition());
    }
}

void MainWindow::UpdateGridPosition(FPuzzleWidget* Widget, const FGridPosition& Position)
{
    if(PuzzleGrid_->itemAtPosition(Position.Row, Position.Column))
    {
        PuzzleGrid_->removeWidget(Widget);
    }
    PuzzleGrid_->addWidget(Widget, Position.Row, Position.Column);
}

void MainWindow::SwapWithEmptyPuzzle(int WidgetId)
{
    Player_.CurrentGame.get()->OnPuzzleClick(WidgetId);
    UpdateGrid();

    if(Player_.CurrentGame.get()->bWin)
    {
        ShowWinDialog();
    }
}

void MainWindow::ShowWinDialog()
{
    WinDialog_.show();
}
