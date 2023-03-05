#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "puzzlewidget.h"
#include "game/game.h"

#include <QGridLayout>
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE


typedef std::vector<std::unique_ptr<FPuzzleWidget>> FPuzzleWidgets;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    FGame Game_;
    Ui::MainWindow *Ui_;
    FPuzzleWidgets PuzzleWidgets_;
    QGridLayout *PuzzleGrid_;

public:
    MainWindow(QWidget *Parent = nullptr);
    ~MainWindow();

private:
    void NewGame(FDifficulty Difficulty);
    void InitPuzzleWidgets();
    void UpdateGridPosition(FPuzzleWidget* Widget, const FGridPosition& Position);
    void SwapWithEmptyPuzzle(int WidgetId);
    void ShowWinDialog();
};

#endif // MAINWINDOW_H
