#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>

#include "puzzlewidget.h"

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

public:
    constexpr static int GridSize{5};
    constexpr static int PuzzleNumber{GridSize * GridSize - 1};

private:
    FGridPosition EmptyPuzzlePosition_;
    Ui::MainWindow *Ui_;
    FPuzzleWidgets PuzzleWidgets_;
    QGridLayout *PuzzleGrid_;

public:
    MainWindow(QWidget *Parent = nullptr);
    ~MainWindow();

private:
    void initPuzzleWidgets();
    void SwapWithEmptyPuzzle(int WidgetId);
    bool CanSwapWithEmptyPuzzle(const FGridPosition& Position);
};

#endif // MAINWINDOW_H
