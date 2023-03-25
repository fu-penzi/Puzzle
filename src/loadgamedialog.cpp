#include "loadgamedialog.h"
#include "ui_loadgamedialog.h"
#include <iostream>

FLoadGameDialog::FLoadGameDialog(QWidget *parent) :
    QDialog(parent),
    Ui(new Ui::LoadGameDialog)
{
    Ui->setupUi(this);

    SaveListModel = new QStringListModel(this);
    Ui->saveList->setModel(SaveListModel);
    Ui->saveList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(Ui->saveList, &QListView::doubleClicked, this, [&](const QModelIndex& index)
    {
        emit OnSaveSelect(index.data().toString().toStdString());
        hide();
    });
}

FLoadGameDialog::~FLoadGameDialog()
{
    delete Ui;
}

void FLoadGameDialog::SetGameSaves(const std::vector<std::string> &NewGameSaves)
{
    GameSaves.clear();
    for (const auto& Save : NewGameSaves)
    {
        GameSaves.emplace_back(QString::fromStdString(Save));
    }
    SaveListModel->setStringList(GameSaves);
}
