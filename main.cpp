#include "mainwindow.h"
#include "qgridlayout.h"
#include "qpushbutton.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QGridLayout* grid = w.findChild<QObject*>("puzzle")->findChild<QGridLayout *>("gridLayout");

    constexpr int gridSize = 5;
    std::vector<std::unique_ptr<QPushButton>> puzzle;
    puzzle.reserve(gridSize);

    for (int i = 0; i < pow(gridSize, 2); ++i) {
        puzzle.emplace_back(new QPushButton("Test"));
        grid->addWidget(puzzle[i].get(), i / gridSize, i % gridSize);
        puzzle[i].get()->grabGesture(Qt::SwipeGesture);

    }


    w.show();
    return a.exec();
}
