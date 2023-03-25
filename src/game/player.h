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
    FPlayer();

    std::unique_ptr<FGame> CurrentGame{};
    FPlayerScores PlayerScores{"Profiles/Player/Score"};
    std::vector<std::string> GameSaves{};

    void NewGame(EDifficulty Difficulty, EMode GameMode);
    void SaveGame();
    void FinishGame();
    void LoadGame(std::string SaveName);

    bool Pause() const;

private:
    bool Pause_{};

    const std::string ProfilesDirPath_ {"Profiles"};
    const std::string ProfilePath_ {ProfilesDirPath_ + "/Player"};
    const std::string SaveDirPath_ {ProfilePath_ + "/Saves"};

    void UpdateGameSaves();
    void RemoveSave(std::string Filename);
};

#endif // PLAYER_H
