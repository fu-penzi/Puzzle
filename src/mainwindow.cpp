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
    Bkgnd = Bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette Palette;
    Palette.setBrush(QPalette::Window, Bkgnd);
    setPalette(Palette);

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
        if(Player_.CurrentGame->IsFinished() && !Player_.Pause())
        {
            Player_.FinishGame();
            ShowWinDialog();
        }
    });
    Timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete Ui_;
}

void MainWindow::InitActions()
{
    const QList<QAction*> GameActionList = {&NewGameAction_, &SaveGameAction_, &LoadGameAction_, &ScoreAction_};
    for (QAction* Action : GameActionList)
    {
        Action->setParent(Ui_->gameMenu);
        Ui_->gameMenu->addAction(Action);
    }

    connect(&NewGameAction_, &QAction::triggered, this, &MainWindow::NewGame);
    connect(&SaveGameAction_, &QAction::triggered, this, [&]()
    {
        Player_.SaveGame();
    });
    connect(&LoadGameAction_, &QAction::triggered, this, &MainWindow::ShowLoadGameDialog);
    connect(&ScoreAction_, &QAction::triggered, this, &MainWindow::ShowScoreDialog);

    const QList<QAction*> DifficultyActionList = {&EasyAction_, &MediumAction_, &HardAction_};
    constexpr std::array<EDifficulty, 3> Difficulties{EDifficulty::Easy, EDifficulty::Medium, EDifficulty::Hard};
    InitActionsHandler(DifficultyActionList, Difficulties, Difficulty_);
    InitActionGroup(DifficultyActionList, Ui_->difficultyMenu, DifficultyActionGroup_);

    const QList<QAction*> GameModeActionList = {&FreeSwapAction_, &EmptySwapAction_};
    constexpr std::array<EMode, 2> Modes{EMode::FreeSwap, EMode::EmptySwap};
    InitActionsHandler(GameModeActionList, Modes, GameMode_);
    InitActionGroup(GameModeActionList, Ui_->gameModeMenu, GameModeActionGroup_);

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
    if(Ui_->puzzleGrid->itemAtPosition(Position.Row, Position.Column))
    {
        Ui_->puzzleGrid->removeWidget(Widget);
    }
    Ui_->puzzleGrid->addWidget(Widget, Position.Row, Position.Column);
}

void MainWindow::SwapWithEmptyPuzzle(int WidgetId)
{
    Player_.CurrentGame->OnPuzzleClick(WidgetId);
    UpdateGrid();

    if(Player_.CurrentGame->IsFinished() && !Player_.Pause())
    {
        Player_.FinishGame();
        ShowWinDialog();
    }
}

void MainWindow::ShowWinDialog()
{
    WinDialog_.Show(Player_.CurrentGame->bWin());
}

void MainWindow::ShowLoadGameDialog()
{
    LoadGameDialog_.SetGameSaves(Player_.GameSaves);
    LoadGameDialog_.show();
}

void MainWindow::ShowScoreDialog()
{
    ScoreDialog_.Show(Player_.PlayerScores);
}

void MainWindow::UpdateLabels()
{
    QString GameIdLabelText = QString{"Game: " + QString::number(Player_.CurrentGame->GameId())};
    QString MovesLabelText = QString("Moves: " + QString::number(Player_.CurrentGame->Moves()));
    QString TimeLabelText = QString("Time: " +  QString::number(Player_.CurrentGame->Time()) + "s");
    Ui_->gameIdLabel->setText(GameIdLabelText);
    Ui_->movesLabel->setText(MovesLabelText);
    Ui_->timeLabel->setText(TimeLabelText);
}

void MainWindow::UpdateCheckedActions()
{
    switch (Player_.CurrentGame->GameConfig().Difficulty())
    {
    case EDifficulty::Easy:
        EasyAction_.setChecked(true);
        break;
    case EDifficulty::Medium:
        MediumAction_.setChecked(true);
        break;
    case EDifficulty::Hard:
        HardAction_.setChecked(true);
        break;
    default:
        break;
    }

    switch (Player_.CurrentGame->GameConfig().Mode())
    {
    case EMode::EmptySwap:
        EmptySwapAction_.setChecked(true);
        break;
    case EMode::FreeSwap:
        FreeSwapAction_.setChecked(true);
        break;
    default:
        break;
    }
}
