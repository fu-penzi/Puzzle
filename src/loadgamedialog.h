#ifndef LOADGAMEDIALOG_H
#define LOADGAMEDIALOG_H

#include <QStringListModel>
#include <QListView>
#include <QDialog>

namespace Ui
{
class LoadGameDialog;
}

class FLoadGameDialog : public QDialog
{
    Q_OBJECT

public:
    QListView* SaveList;
    QStringListModel* SaveListModel;
    QString Save;

    explicit FLoadGameDialog(QWidget *parent = nullptr);
    ~FLoadGameDialog();

    void SetGameSaves(const std::vector<std::string> &NewGameSaves);

private:
    Ui::LoadGameDialog *Ui;
    QStringList GameSaves;


signals:
    void OnSaveSelect(std::string SelectedSave);
};

#endif // LOADGAMEDIALOG_H
