#include "loadgamedialog.h"
#include "ui_loadgamedialog.h"
#include <iostream>

FLoadGameDialog::FLoadGameDialog(QWidget *parent) :
    QDialog(parent),
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

FLoadGameDialog::~FLoadGameDialog()
{
    delete Ui_;
}

void FLoadGameDialog::SetGameSaves(const std::vector<std::string> &NewGameSaves)
{
    GameSaves_.clear();
    for (const auto& Save : NewGameSaves)
    {
        GameSaves_.emplace_back(QString::fromStdString(Save));
    }
    SaveListModel_->setStringList(GameSaves_);
}
