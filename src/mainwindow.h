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


typedef std::vector<std::shared_ptr<UIPuzzleWidget>> FPuzzleWidgets;

/**
 *  @author Piotr Nowak
 *  @brief Application main window.
 */
class UIMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * Constructor used to initialize class.
     * @param Parent parent widget
     */
    UIMainWindow(QWidget* Parent = nullptr);
    ~UIMainWindow();

private:
    FPlayer Player_;
    FPuzzleWidgets PuzzleWidgets_;

    Ui::MainWindow *Ui_;
    UIMenu* Menu;

    UIWinDialog WinDialog_;
    UILoadGameDialog LoadGameDialog_;

private:
    void InitPuzzleWidgets();
    void InitGame();
    void UpdateGrid();
    void UpdateGridPosition(UIPuzzleWidget* Widget, const FGridPosition& Position);
    void SwapWithEmptyPuzzle(int WidgetId);
    void ShowWinDialog();
    void UpdateLabels();
    void UpdateTimer();
};

#endif // MAINWINDOW_H
