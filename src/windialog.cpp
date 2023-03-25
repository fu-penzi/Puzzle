#include "windialog.h"
#include "ui_windialog.h"

FWinDialog::FWinDialog(QWidget *parent)
    : QDialog{parent}
    , Ui_{new Ui:: WinDialog}
{
    Ui_->setupUi(this);
}

FWinDialog::~FWinDialog()
{
    delete Ui_;
}

void FWinDialog::Show(bool bWin)
{
    QString LabelText{bWin ? "You win :)" : "You lose :(" };
    Ui_->label->setText(LabelText);
    show();
}

