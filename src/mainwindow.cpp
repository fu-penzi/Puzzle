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

    GameIdLabel_ = findChild<QObject*>("puzzle")->findChild<QLabel *>("gameId");
    TimeLabel_ = findChild<QObject*>("puzzle")->findChild<QLabel *>("time");
    MovesLabel_ = findChild<QObject*>("puzzle")->findChild<QLabel *>("moves");

    InitActions();

    connect(&LoadGameDialog_, &FLoadGameDialog::OnSaveSelect, this, [&](std::string SaveName)
    {
        Player_.LoadGame(SaveName);
        UpdateCheckedActions();
        UpdateLabels();
        PuzzleWidgets_.clear();
        PuzzleWidgets_.reserve(Player_.CurrentGame->GameConfig().PuzzleNumber());
        InitPuzzleWidgets();
    });

    QTimer* Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, [&]()
    {
        Player_.CurrentGame->UpdateTimer();
        UpdateLabels();
    });
    Timer->start(1000);
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
    SaveGame_.setParent(GameMenu);
    LoadGame_.setParent(GameMenu);

    connect(&NewGame_, &QAction::triggered, this, &MainWindow::NewGame);
    connect(&SaveGame_, &QAction::triggered, this, [&]()
    {
        Player_.SaveGame();
    });
    connect(&LoadGame_, &QAction::triggered, this, [&]()
    {
        LoadGameDialog_.SetGameSaves(Player_.GameSaves);
        LoadGameDialog_.show();
    });

    GameMenu->addAction(&NewGame_);
    GameMenu->addAction(&SaveGame_);
    GameMenu->addAction(&LoadGame_);

    const QList<QAction*> DifficultyActionList = {&Easy_, &Medium_, &Hard_};
    constexpr std::array<EDifficulty, 3> Difficulties{EDifficulty::Easy, EDifficulty::Medium, EDifficulty::Hard};
    InitActionsHandler(DifficultyActionList, Difficulties, Difficulty_);
    InitActionGroup(DifficultyActionList, DifficultyMenu, DifficultyActionGroup_);

    const QList<QAction*> GameActionList = {&FreeSwap_, &EmptySwap_};
    constexpr std::array<EMode, 2> Modes{EMode::FreeSwap, EMode::EmptySwap};
    InitActionsHandler(GameActionList, Modes, GameMode_);
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
    for (auto& Puzzle: Player_.CurrentGame->PuzzleVector())
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
    Player_.NewGame(Difficulty_, GameMode_);
    UpdateLabels();
    PuzzleWidgets_.clear();
    PuzzleWidgets_.reserve(Player_.CurrentGame->GameConfig().PuzzleNumber());
    InitPuzzleWidgets();
}

void MainWindow::UpdateGrid()
{
    auto& PuzzleVector = Player_.CurrentGame->PuzzleVector();
    for(int i = 0; i < PuzzleVector.size(); ++i)
    {
        if(PuzzleVector[i].PuzzleType() == EPuzzleType::EMPTY)
        {
            continue;
        }
        UpdateGridPosition(PuzzleWidgets_[i].get(), PuzzleVector[i].GridPosition());
    }
    UpdateLabels();
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
    Player_.CurrentGame->OnPuzzleClick(WidgetId);
    UpdateGrid();

    if(Player_.CurrentGame->bWin())
    {
        ShowWinDialog();
    }
}

void MainWindow::ShowWinDialog()
{
    WinDialog_.show();
}

void MainWindow::UpdateLabels()
{
    QString GameIdLabelText = QString::fromStdString("Game: " + std::to_string(Player_.CurrentGame->GameId()));
    GameIdLabel_->setText(GameIdLabelText);

    QString MovesLabelText = QString::fromStdString("Moves: " + std::to_string(Player_.CurrentGame->Moves()));
    MovesLabel_->setText(MovesLabelText);

    QString TimeLabelText = QString::fromStdString("Time: " + std::to_string(Player_.CurrentGame->Time()) + "s");
    TimeLabel_->setText(TimeLabelText);
}

void MainWindow::UpdateCheckedActions()
{
    switch (Player_.CurrentGame->GameConfig().Difficulty())
    {
    case EDifficulty::Easy:
        Easy_.setChecked(true);
        break;
    case EDifficulty::Medium:
        Medium_.setChecked(true);
        break;
    case EDifficulty::Hard:
        Hard_.setChecked(true);
        break;
    default:
        break;
    }

    switch (Player_.CurrentGame->GameConfig().Mode())
    {
    case EMode::EmptySwap:
        EmptySwap_.setChecked(true);
        break;
    case EMode::FreeSwap:
        FreeSwap_.setChecked(true);
        break;
    default:
        break;
    }
}
