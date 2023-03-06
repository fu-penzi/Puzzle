#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "puzzlewidget.h"
#include "game/game.h"
#include "windialog.h"

#include <QGridLayout>
#include <QMainWindow>
#include <QtWidgets>

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
    std::unique_ptr<FGame> Game_;
    Ui::MainWindow *Ui_;
    FPuzzleWidgets PuzzleWidgets_;
    QGridLayout *PuzzleGrid_;
    FWinDialog WinDialog_;
    FDifficulty Difficulty;
    QAction* NewGame_;

    QActionGroup* DifficultyActions_;
    QAction* Easy_;
    QAction* Medium_;
    QAction* Hard_;

public:
    MainWindow(QWidget *Parent = nullptr);
    ~MainWindow();

private:
    void InitActions();
    void InitDifficultyAction();
    void InitPuzzleWidgets();
    void NewGame(FDifficulty Difficulty);
    void UpdateGridPosition(FPuzzleWidget* Widget, const FGridPosition& Position);
    void SwapWithEmptyPuzzle(int WidgetId);
    void ShowWinDialog();
};

#endif // MAINWINDOW_H
