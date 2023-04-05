#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QPushButton>

class FPuzzleWidget : public QPushButton
{
    Q_OBJECT

public:
    int Id() const;

private:
    const int Id_;

public:
    explicit FPuzzleWidget(int Id, QWidget *Parent = nullptr);

signals:
    void OnClick(int Id);
};
#endif // PUZZLEWIDGET_H
