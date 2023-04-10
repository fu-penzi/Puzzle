#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QPushButton>

/**
 *  @author Piotr Nowak
 *  @brief Puzzle button widget
 */
class UIPuzzleWidget : public QPushButton
{
    Q_OBJECT

public:

    /**
     * Add menus to menu bar and initialize event handlers
     * @param Id id of puzzle to display on button
     * @param Parent parent widget
     */
    explicit UIPuzzleWidget(int Id, QWidget* Parent = nullptr);


    /**
     * Getter
     * @return id of puzzle to display on button
     */
    int Id() const;

signals:

    /**
     * Emit button click signal
     * @param Id id of puzzle
     */
    void OnClick(int Id);

private:
    const int Id_;
};
#endif // PUZZLEWIDGET_H
