#include "windialog.h"
#include "ui_windialog.h"

UIWinDialog::UIWinDialog(QWidget *Parent)
    : QDialog{Parent}
    , Ui_{new Ui:: WinDialog}
{
    Ui_->setupUi(this);
}

UIWinDialog::~UIWinDialog()
{
    delete Ui_;
}

void UIWinDialog::Show(bool bWin)
{
    QString LabelText{bWin ? "You win :)" : "You lose :(" };
    Ui_->label->setText(LabelText);
    show();
}

