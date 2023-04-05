#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game/player.h"
#include "loadgamedialog.h"
#include "menu.h"
#include "puzzlewidget.h"
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
    FPlayer Player_;
    FPuzzleWidgets PuzzleWidgets_;

    Ui::MainWindow *Ui_;
    FMenu* Menu;

    FWinDialog WinDialog_;
    FLoadGameDialog LoadGameDialog_;

public:
    MainWindow(QWidget *Parent = nullptr);
    ~MainWindow();

private:
    void InitPuzzleWidgets();
    void InitGame();
    void UpdateGrid();
    void UpdateGridPosition(FPuzzleWidget* Widget, const FGridPosition& Position);
    void SwapWithEmptyPuzzle(int WidgetId);
    void ShowWinDialog();
    void UpdateLabels();
    void UpdateTimer();
};

#endif // MAINWINDOW_H
