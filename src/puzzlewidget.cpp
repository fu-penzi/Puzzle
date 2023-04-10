#include "puzzlewidget.h"

#include <QPushButton>
#include <QString>
#include <iostream>

UIPuzzleWidget::UIPuzzleWidget(int Id, QWidget *Parent)
    : QPushButton{QString::fromStdString(std::to_string(Id).c_str()), Parent}
    , Id_{Id}
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("QPushButton{font-size: 26px;}");
    connect(this, &QPushButton::clicked, this, [&]()
    {
        emit OnClick(Id_);
    });
}

int UIPuzzleWidget::Id() const
{
    return Id_;
}
