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

private:
    Ui::LoadGameDialog *Ui_;
    QStringList GameSaves_;
    QStringListModel* SaveListModel_;
    QString Save_;

public:
    explicit FLoadGameDialog(QWidget *parent = nullptr);
    ~FLoadGameDialog();

    void SetGameSaves(const std::vector<std::string>& NewGameSaves);


signals:
    void OnSaveSelect(std::string SelectedSave);
};

#endif // LOADGAMEDIALOG_H
