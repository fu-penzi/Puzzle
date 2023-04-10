#ifndef MENU_H
#define MENU_H

#include "game/gameconfig.h"
#include "game/player.h"
#include "loadgamedialog.h"
#include "scoredialog.h"

#include <QActionGroup>
#include <QMenuBar>
#include <QWidget>

/**
 *  @author Piotr Nowak
 *  @brief Menu bar widget used to configure game and display player scores.
 */
class UIMenu : public QWidget
{
    Q_OBJECT

public:

    /**
     * Constructor used to initialize class.
     * @param Parent parent widget
     */
    explicit UIMenu(QWidget* Parent = nullptr);

    /**
     * Add menus to menu bar and initialize event handlers
     * @param MenuBar menu bar widget
     * @param Player player instance
     */
    void InitMenu(QMenuBar *MenuBar, FPlayer* Player);

signals:
    /**
     * Emit start game signal
     */
    void StartGame();

private:
    FPlayer* Player_;
    EDifficulty Difficulty_{EDifficulty::Default};
    EMode GameMode_{EMode::Default};

    UILoadGameDialog LoadGameDialog_;
    UIScoreDialog ScoreDialog_;

    QMenuBar* MenuBar_;
    QMenu GameMenu_{"Game"};
    QMenu DifficultyMenu_{"Difficulty"};
    QMenu GameModeMenu_{"Game mode"};

    QAction NewGameAction_{"New game"};
    QAction SaveGameAction_{"Save"};
    QAction LoadGameAction_{"Load"};
    QAction ScoreAction_{"Score"};

    QActionGroup DifficultyActionGroup_{nullptr};
    QAction EasyAction_{"Easy"};
    QAction MediumAction_{"Medium"};
    QAction HardAction_{"Hard"};

    QActionGroup GameModeActionGroup_{nullptr};
    QAction FreeSwapAction_{"Free swapping"};
    QAction EmptySwapAction_{"Empty tile swapping"};

private:
    void NewGame();
    void InitActions();
    void InitActionGroup(QList<QAction*> Actions, QMenu* Menu, QActionGroup& ActionGroup);
    void UpdateCheckedActions();
    void ShowScoreDialog();
    void ShowLoadGameDialog();

    template<typename E, std::size_t N>
    void InitActionsHandler(QList<QAction*> Actions, std::array<E, N> Enum, E& ToSet)
    {
        for(int i = 0; i < N; ++i)
        {
            connect(Actions[i], &QAction::triggered, this, [&, i, Enum]()
            {
                ToSet = Enum[i];
                NewGame();
            });

            if(Enum[i] == E::Default)
            {
                Actions[i]->setChecked(true);
            }
        }
    }
};

#endif // MENU_H
