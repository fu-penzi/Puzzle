#ifndef PLAYER_H
#define PLAYER_H


#include "game.h"
#include "playerscores.h"

#include <memory>
#include <string>
#include <vector>

class FPlayer
{
public:

    const FPlayerScores& PlayerScores() const;
    const std::vector<std::string>& GameSaves() const;
    bool Pause() const;

private:
    std::unique_ptr<FGame> CurrentGame_{};
    FPlayerScores PlayerScores_{"Profiles/Player/Score"};
    std::vector<std::string> GameSaves_{};
    bool Pause_{};

    const std::string ProfilesDirPath_ {"Profiles"};
    const std::string ProfilePath_ {ProfilesDirPath_ + "/Player"};
    const std::string SaveDirPath_ {ProfilePath_ + "/Saves"};


public:
    FPlayer();

    void NewGame(EDifficulty Difficulty, EMode GameMode);
    void SaveGame();
    void FinishGame();
    void LoadGame(std::string SaveName);

    FGame* CurrentGame();

private:
    void UpdateGameSaves();
    void RemoveSave(std::string Filename);
};

#endif // PLAYER_H
