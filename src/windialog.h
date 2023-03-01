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
public:
    explicit FWinDialog(QWidget *parent = nullptr);
    ~FWinDialog();

private:
    Ui::WinDialog *Ui_;

signals:

};

#endif // WINDIALOG_H
