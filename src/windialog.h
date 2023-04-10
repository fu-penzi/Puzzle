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

/**
 *  @author Piotr Nowak
 *  @brief End of game dialog window
 */
class UIWinDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * Constructor used to initialize class.
     * @param Parent parent widget
     */
    explicit UIWinDialog(QWidget* Parent = nullptr);
    ~UIWinDialog();

    /**
     * Show dialog window.
     * @param bWin is game won or lost
     */
    void Show(bool bWin);

private:
    Ui::WinDialog *Ui_;
};

#endif // WINDIALOG_H
