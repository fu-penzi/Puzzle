#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game/player.h"
#include "loadgamedialog.h"
#include "puzzlewidget.h"
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

    Ui::MainWindow *Ui_;
    FPuzzleWidgets PuzzleWidgets_;
    QGridLayout *PuzzleGrid_{};
    FWinDialog WinDialog_;
    FLoadGameDialog LoadGameDialog_;

    QAction NewGame_{"New game"};
    QAction SaveGame_{"Save"};
    QAction LoadGame_{"Load"};

    QActionGroup DifficultyActionGroup_{nullptr};
    QAction Easy_{"Easy"};
    QAction Medium_{"Medium"};
    QAction Hard_{"Hard"};

    QActionGroup GameModeActionGroup_{nullptr};
    QAction FreeSwap_{"Free swapping"};
    QAction EmptySwap_{"Empty tile swapping"};


    QLabel* GameIdLabel_;
    QLabel* TimeLabel_;
    QLabel* MovesLabel_;

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
    void UpdateLabels();
    void UpdateCheckedActions();

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
