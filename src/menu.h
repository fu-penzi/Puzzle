#ifndef MENU_H
#define MENU_H

#include "game/gameconfig.h"
#include "game/player.h"
#include "loadgamedialog.h"
#include "scoredialog.h"

#include <QActionGroup>
#include <QMenuBar>
#include <QWidget>

class FMenu : public QWidget
{
    Q_OBJECT

private:
    FPlayer* Player_;
    EDifficulty Difficulty_{EDifficulty::Default};
    EMode GameMode_{EMode::Default};

    FLoadGameDialog LoadGameDialog_;
    ScoreDialog ScoreDialog_;

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

public:
    explicit FMenu(QWidget *Parent = nullptr);

    void InitMenu(QMenuBar *MenuBar, FPlayer* Player);

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

signals:
    void StartGame();
};

#endif // MENU_H
