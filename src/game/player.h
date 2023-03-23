#ifndef PLAYER_H
#define PLAYER_H


#include "game.h"
#include "score.h"

#include <memory>
#include <string>
#include <vector>

class FPlayer
{
public:
    FPlayer();

    std::string Name{"Player"};
    std::unique_ptr<FGame> CurrentGame{};
    FScore Score{};
    std::vector<std::string> GameSaves{};

    void NewGame(EDifficulty Difficulty, EMode GameMode);
    void SaveGame();
    void LoadGame(std::string SaveName);


private:
    void UpdateScoreFile();
    void UpdateGameSaves();

    const std::string ProfilesDirPath {"Profiles"};
    const std::string ProfilePath {ProfilesDirPath + "/" + Name};
    const std::string ScorePath {ProfilePath + "/Score"};
    const std::string SaveDirPath {ProfilePath + "/Saves"};
};

#endif // PLAYER_H
