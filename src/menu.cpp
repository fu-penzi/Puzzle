#include "menu.h"

UIMenu::UIMenu(QWidget *Parent)
    : QWidget{Parent}
{

}

void UIMenu::InitMenu(QMenuBar* MenuBar, FPlayer* Player)
{
    MenuBar_ = MenuBar;
    Player_ = Player;
    MenuBar->addMenu(&GameMenu_);
    MenuBar->addMenu(&DifficultyMenu_);
    MenuBar->addMenu(&GameModeMenu_);


    InitActions();

    connect(&LoadGameDialog_, &UILoadGameDialog::OnSaveSelect, this, [&](std::string SaveName)
    {
        Player_->LoadGame(SaveName);
        UpdateCheckedActions();
        emit StartGame();
    });

}

void UIMenu::InitActions()
{
    const QList<QAction*> GameActionList = {&NewGameAction_, &SaveGameAction_, &LoadGameAction_, &ScoreAction_};
    for (QAction* Action : GameActionList)
    {
        Action->setParent(&GameMenu_);
        GameMenu_.addAction(Action);
    }

    connect(&NewGameAction_, &QAction::triggered, this, &UIMenu::NewGame);
    connect(&SaveGameAction_, &QAction::triggered, this, [&]()
    {
        Player_->SaveGame();
    });
    connect(&LoadGameAction_, &QAction::triggered, this, &UIMenu::ShowLoadGameDialog);
    connect(&ScoreAction_, &QAction::triggered, this, &UIMenu::ShowScoreDialog);

    const QList<QAction*> DifficultyActionList = {&EasyAction_, &MediumAction_, &HardAction_};
    constexpr std::array<EDifficulty, 3> Difficulties{EDifficulty::Easy, EDifficulty::Medium, EDifficulty::Hard};
    InitActionsHandler(DifficultyActionList, Difficulties, Difficulty_);
    InitActionGroup(DifficultyActionList, &DifficultyMenu_, DifficultyActionGroup_);

    const QList<QAction*> GameModeActionList = {&FreeSwapAction_, &EmptySwapAction_};
    constexpr std::array<EMode, 2> Modes{EMode::FreeSwap, EMode::EmptySwap};
    InitActionsHandler(GameModeActionList, Modes, GameMode_);
    InitActionGroup(GameModeActionList, &GameModeMenu_, GameModeActionGroup_);

    NewGame();
}

void UIMenu::InitActionGroup(QList<QAction *> Actions, QMenu *Menu, QActionGroup &ActionGroup)
{
    ActionGroup.setParent(Menu);
    ActionGroup.setExclusive(true);
    Menu->addActions(Actions);
    for (auto& Action : Actions)
    {
        ActionGroup.addAction(Action);
        Action->setCheckable(true);
    }
}

void UIMenu::UpdateCheckedActions()
{
    switch (Player_->CurrentGame()->GameConfig().Difficulty())
    {
    case EDifficulty::Easy:
        EasyAction_.setChecked(true);
        break;
    case EDifficulty::Medium:
        MediumAction_.setChecked(true);
        break;
    case EDifficulty::Hard:
        HardAction_.setChecked(true);
        break;
    default:
        break;
    }

    switch (Player_->CurrentGame()->GameConfig().Mode())
    {
    case EMode::EmptySwap:
        EmptySwapAction_.setChecked(true);
        break;
    case EMode::FreeSwap:
        FreeSwapAction_.setChecked(true);
        break;
    default:
        break;
    }
}

void UIMenu::ShowScoreDialog()
{
    ScoreDialog_.Show(Player_->PlayerScores());
}

void UIMenu::ShowLoadGameDialog()
{
    LoadGameDialog_.SetGameSaves(Player_->GameSaves());
    LoadGameDialog_.show();
}

void UIMenu::NewGame()
{
    Player_->NewGame(Difficulty_, GameMode_);
    emit StartGame();
}
