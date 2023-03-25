#include "scoredialog.h"
#include "ui_scoredialog.h"
#include "game/gameconfig.h"

#include <QTableView>

ScoreDialog::ScoreDialog(QWidget *parent) :
    QDialog(parent),
    Ui_(new Ui::ScoreDialog)
{
    Ui_->setupUi(this);
    TableViewModel_ = new QStandardItemModel(Ui_->scoreTable);
    Ui_->scoreTable->setModel(TableViewModel_);
    Ui_->scoreTable->horizontalHeader()->setStretchLastSection(true);
}

ScoreDialog::~ScoreDialog()
{
    delete Ui_;
}

void ScoreDialog::Show(const FPlayerScores& PlayerScores)
{
    Ui_->totalLabel->setText(QString::number(PlayerScores.GamesPlayed()));
    Ui_->wonLabel->setText(QString::number(PlayerScores.GamesWon()));
    Ui_->lostLabel->setText(QString::number(PlayerScores.GamesLost()));

    TableViewModel_->clear();
    TableViewModel_->setHorizontalHeaderLabels(
    {"Game Id", "Result", "Remaining time", "Moves", "Difficulty", "Mode"}
    );
    for (auto& Score : PlayerScores.Scores())
    {
        AddRow(Score);
    }
    show();
}

void ScoreDialog::AddRow(FScore Score)
{
    QStandardItem* GameId =  new QStandardItem(QString::number(Score.GameId));
    QStandardItem* Result =  Score.bWin ? new QStandardItem("Win") : new QStandardItem("Lose");
    QStandardItem* RemainingTime =  new QStandardItem(QString::number(Score.RemainingTime) + QString{"s"});
    const QList<QStandardItem*> ScoreList
    {
        GameId,
        Result,
        RemainingTime,
        new QStandardItem(QString::number(Score.Moves)),
        new QStandardItem(QString::fromStdString(FGameConfig::DifficultyToString(Score.Difficulty))),
        new QStandardItem(QString::fromStdString(FGameConfig::ModeToString(Score.GameMode))),
    };

    for (QStandardItem* Item : ScoreList)
    {
        Item->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    TableViewModel_->appendRow(ScoreList);
}
