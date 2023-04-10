#ifndef LOADGAMEDIALOG_H
#define LOADGAMEDIALOG_H

#include <QStringListModel>
#include <QListView>
#include <QDialog>

namespace Ui
{
class LoadGameDialog;
}

/**
 *  @author Piotr Nowak
 *  @brief Load game dialog window.
 */
class UILoadGameDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * Constructor used to initialize class.
     * @param Parent parent widget
     */
    explicit UILoadGameDialog(QWidget* Parent = nullptr);
    ~UILoadGameDialog();

    /**
     * Setter
     * @param NewGameSaves game save vector to display
     */
    void SetGameSaves(const std::vector<std::string>& NewGameSaves);

signals:

    /**
     * Emit save select signal
     * @param SelectedSave selected save filename
     */
    void OnSaveSelect(std::string SelectedSave);

private:
    Ui::LoadGameDialog *Ui_;
    QStringList GameSaves_;
    QStringListModel* SaveListModel_;
    QString Save_;
};

#endif // LOADGAMEDIALOG_H
