#include "loadgamedialog.h"
#include "ui_loadgamedialog.h"
#include <iostream>

UILoadGameDialog::UILoadGameDialog(QWidget *Parent) :
    QDialog(Parent),
    Ui_(new Ui::LoadGameDialog)
{
    Ui_->setupUi(this);

    SaveListModel_ = new QStringListModel(this);
    Ui_->saveList->setModel(SaveListModel_);
    Ui_->saveList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(Ui_->saveList, &QListView::doubleClicked, this, [&](const QModelIndex& index)
    {
        emit OnSaveSelect(index.data().toString().toStdString());
        hide();
    });
}

UILoadGameDialog::~UILoadGameDialog()
{
    delete Ui_;
}

void UILoadGameDialog::SetGameSaves(const std::vector<std::string> &NewGameSaves)
{
    GameSaves_.clear();
    for (const auto& Save : NewGameSaves)
    {
        GameSaves_.emplace_back(QString::fromStdString(Save));
    }
    SaveListModel_->setStringList(GameSaves_);
}
