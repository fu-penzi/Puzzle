#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windialog.h"

#include <QGridLayout>
#include <QPalette>

UIMainWindow::UIMainWindow(QWidget *Parent)
    : QMainWindow(Parent)
    , Ui_{new Ui::MainWindow}
{
    Ui_->setupUi(this);
    Menu = new UIMenu(this->centralWidget());
    Menu->InitMenu(Ui_->menuBar, &Player_);

    QPixmap Bkgnd(":/bg.png");
    Bkgnd = Bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette Palette;
    Palette.setBrush(QPalette::Window, Bkgnd);
    setPalette(Palette);


    connect(Menu, &UIMenu::StartGame, this, &UIMainWindow::InitGame);

    QTimer* Timer = new QTimer(this);
    connect(Timer, &QTimer::timeout, this, [&]()
    {
        Player_.CurrentGame()->UpdateTimer();
        UpdateLabels();
        if(Player_.CurrentGame()->IsFinished() && !Player_.Pause())
        {
            Player_.FinishGame();
            ShowWinDialog();
        }
    });
    Timer->start(1000);

    InitGame();
}

UIMainWindow::~UIMainWindow()
{
    delete Ui_;
}

void UIMainWindow::InitPuzzleWidgets()
{
    for (auto& Puzzle: Player_.CurrentGame()->PuzzleVector())
    {
        if(Puzzle.PuzzleType() == EPuzzleType::EMPTY)
        {
            continue;
        }
        auto Widget = std::make_shared<UIPuzzleWidget>(Puzzle.Id());
        PuzzleWidgets_.push_back(Widget);
        connect(Widget.get(), &UIPuzzleWidget::OnClick, this, &UIMainWindow::SwapWithEmptyPuzzle);
    }
    UpdateGrid();
}

void UIMainWindow::InitGame()
{
    UpdateLabels();
    PuzzleWidgets_.clear();
    PuzzleWidgets_.reserve(Player_.CurrentGame()->GameConfig().PuzzleNumber());
    InitPuzzleWidgets();
}

void UIMainWindow::UpdateGrid()
{
    auto& PuzzleVector = Player_.CurrentGame()->PuzzleVector();
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

void UIMainWindow::UpdateGridPosition(UIPuzzleWidget* Widget, const FGridPosition& Position)
{
    if(Ui_->puzzleGrid->itemAtPosition(Position.Row, Position.Column))
    {
        Ui_->puzzleGrid->removeWidget(Widget);
    }
    Ui_->puzzleGrid->addWidget(Widget, Position.Row, Position.Column);
}

void UIMainWindow::SwapWithEmptyPuzzle(int WidgetId)
{
    Player_.CurrentGame()->OnPuzzleClick(WidgetId);
    UpdateGrid();

    if(Player_.CurrentGame()->IsFinished() && !Player_.Pause())
    {
        Player_.FinishGame();
        ShowWinDialog();
    }
}

void UIMainWindow::ShowWinDialog()
{
    WinDialog_.Show(Player_.CurrentGame()->bWin());
}

void UIMainWindow::UpdateLabels()
{
    QString GameIdLabelText = QString{"Game: " + QString::number(Player_.CurrentGame()->GameId())};
    QString MovesLabelText = QString("Moves: " + QString::number(Player_.CurrentGame()->Moves()));
    QString TimeLabelText = QString("Time: " +  QString::number(Player_.CurrentGame()->Time()) + "s");
    Ui_->gameIdLabel->setText(GameIdLabelText);
    Ui_->movesLabel->setText(MovesLabelText);
    Ui_->timeLabel->setText(TimeLabelText);
}
