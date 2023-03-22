#include "player.h"
#include "gameemptyswap.h"
#include "gamefreeswap.h"

#include <direct.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>

FPlayer::FPlayer()
{
    mkdir(ProfilesDirPath.c_str());
    mkdir(ProfilePath.c_str());
    mkdir(SaveDirPath.c_str());

    std::filesystem::path Dir {SaveDirPath};
    for (auto& File : std::filesystem::directory_iterator(Dir))
    {
        GameSaves.emplace_back(std::filesystem::path(File.path()).filename().string());
    }

    SaveGame();
}

void FPlayer::NewGame(EDifficulty Difficulty, EMode GameMode)
{
    if(GameMode == EMode::FreeSwap)
    {
        CurrentGame = std::make_unique<FGameFreeSwap>(Difficulty);
    }
    else
    {
        CurrentGame = std::make_unique<FGameEmptySwap>(Difficulty);
    }
}

void FPlayer::SaveGame()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    const std::string Filename{std::to_string(now->tm_hour)
                               + "."
                               + (now->tm_min < 10 ? "0" + std::to_string(now->tm_min) : std::to_string(now->tm_min))
                               + " "
                               + std::to_string(now->tm_mday) + "-"
                               + std::to_string(now->tm_mon + 1) + "-"
                               + std::to_string(now->tm_year + 1900)
                              };

    std::ofstream File;
    File.open(SaveDirPath + "/" + Filename, std::ios::app);
    File.write((char*)&CurrentGame, sizeof(CurrentGame));
    File.close();
}

void FPlayer::LoadGame(std::string SaveName)
{
    CurrentSave = SaveName;
    std::ifstream File;
    File.open(SaveDirPath + "/" + SaveName, std::ios::in);
    File.seekg(0);
    File.read((char*)&CurrentGame, sizeof(CurrentGame));
    File.close();
}
