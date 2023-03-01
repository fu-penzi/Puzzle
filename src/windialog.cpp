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

