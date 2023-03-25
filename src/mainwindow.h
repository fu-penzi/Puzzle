#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game/player.h"
#include "loadgamedialog.h"
#include "puzzlewidget.h"
#include "scoredialog.h"
#include "windialog.h"

#include <QGridLayout>
#include <QMainWindow>
#include <QtWidgets>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE


typedef std::vector<std::shared_ptr<FPuzzleWidget>> FPuzzleWidgets;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    FPlayer Player_;
    EDifficulty Difficulty_{EDifficulty::Default};
    EMode GameMode_{EMode::Default};
    FPuzzleWidgets PuzzleWidgets_;

    Ui::MainWindow *Ui_;

    FWinDialog WinDialog_;
    FLoadGameDialog LoadGameDialog_;
    ScoreDialog ScoreDialog_;

    QAction NewGameAction_{"New game"};
    QAction SaveGameAction_{"Save"};
    QAction LoadGameAction_{"Load"};
    QAction ScoreAction_{"Score"};

    QActionGroup DifficultyActionGroup_{nullptr};
    QAction EasyAction_{"Easy"};
    QAction MediumAction_{"Medium"};
    QAction HardAction_{"Hard"};

    QActionGroup GameModeActionGroup_{nullptr};
    QAction FreeSwapAction_{"Free swapping"};
    QAction EmptySwapAction_{"Empty tile swapping"};

public:
    MainWindow(QWidget *Parent = nullptr);
    ~MainWindow();

private:
    void InitActions();
    void InitActionGroup(QList<QAction*> Actions, QMenu* Menu, QActionGroup& ActionGroup);
    void InitPuzzleWidgets();
    void NewGame();
    void UpdateGrid();
    void UpdateGridPosition(FPuzzleWidget* Widget, const FGridPosition& Position);
    void SwapWithEmptyPuzzle(int WidgetId);
    void ShowWinDialog();
    void ShowLoadGameDialog();
    void ShowScoreDialog();
    void UpdateLabels();
    void UpdateCheckedActions();
    void UpdateTimer();


    template<typename E, std::size_t N>
    void InitActionsHandler(QList<QAction*> Actions, std::array<E, N> Enum, E& ToSet)
    {
        for(int i = 0; i < N; ++i)
        {
            connect(Actions[i], &QAction::triggered, this, [&, i, Enum]()
            {
                ToSet = Enum[i];
                NewGame();
            });

            if(Enum[i] == E::Default)
            {
                Actions[i]->setChecked(true);
            }
        }
    }
};

#endif // MAINWINDOW_H
