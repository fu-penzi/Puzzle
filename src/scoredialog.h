#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include "game/playerscores.h"
#include <QStandardItemModel>
#include <QDialog>

namespace Ui
{
class ScoreDialog;
}


/**
 *  @author Piotr Nowak
 *  @brief Score dialog wi
 */
class UIScoreDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * Constructor used to initialize class.
     * @param Parent parent widget
     */
    explicit UIScoreDialog(QWidget* Parent = nullptr);
    ~UIScoreDialog();

    /**
     * Display score dialog.
     * @param PlayerScores scores to display
     */
    void Show(const FPlayerScores& PlayerScores);

private:
    QStandardItemModel* TableViewModel_;
    Ui::ScoreDialog *Ui_;

private:
    void AddRow(FScore Score);
};

#endif // SCOREDIALOG_H
