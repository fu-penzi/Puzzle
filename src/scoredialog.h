#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include "game/playerscores.h"
#include "qstandarditemmodel.h"
#include <QDialog>

namespace Ui
{
class ScoreDialog;
}

class ScoreDialog : public QDialog
{
    Q_OBJECT

private:
    QStandardItemModel* TableViewModel_;
    Ui::ScoreDialog *Ui_;

public:
    explicit ScoreDialog(QWidget *parent = nullptr);
    ~ScoreDialog();

    void Show(const FPlayerScores& PlayerScores);

private:
    void AddRow(FScore Score);
};

#endif // SCOREDIALOG_H
