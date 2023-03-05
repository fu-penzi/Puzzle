#include "puzzlewidget.h"

#include <QPushButton>
#include <QString>
#include <iostream>

FPuzzleWidget::FPuzzleWidget(int Id, QWidget *Parent)
    : QPushButton{*new QString(std::to_string(Id).c_str()), Parent}
    , Id_{Id}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(this, &QPushButton::clicked, this, [&]()
    {
        emit OnClick(Id_);
    });
}

int FPuzzleWidget::Id() const
{
    return Id_;
}
