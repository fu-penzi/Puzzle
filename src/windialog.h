#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class WinDialog;
}
QT_END_NAMESPACE

class FWinDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::WinDialog *Ui_;

public:
    explicit FWinDialog(QWidget *parent = nullptr);
    ~FWinDialog();

    void Show(bool bWin);
};

#endif // WINDIALOG_H
