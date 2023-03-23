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

    if(std::filesystem::exists(ScorePath))
    {
        std::ifstream ScoreFile;
        ScoreFile.open(ScorePath, std::ios::in);
        ScoreFile.seekg(0);
        ScoreFile.read((char*)&Score, sizeof(Score));
        ScoreFile.close();
    }
    UpdateGameSaves();
}

void FPlayer::NewGame(EDifficulty Difficulty, EMode GameMode)
{
    ++Score.GamesPlayed;
    if(CurrentGame)
    {
        SaveGame();
    }
    UpdateScoreFile();

    if(GameMode == EMode::FreeSwap)
    {
        CurrentGame = std::make_unique<FGameFreeSwap>(Score.GamesPlayed, Difficulty, GameMode);
    }
    else
    {
        CurrentGame = std::make_unique<FGameEmptySwap>(Score.GamesPlayed, Difficulty, GameMode);
    }

    SaveGame();
}

void FPlayer::SaveGame()
{
    if(!CurrentGame)
    {
        return;
    }

    const std::string Filename{std::to_string(CurrentGame->GameId())};
    std::ofstream File;

    File.open(SaveDirPath + "/" + Filename, std::ios::out | std::ofstream::trunc);
    File.clear();
    File.write((char*)&CurrentGame->GameConfig(), sizeof(FGameConfig));
    File.write((char*)&CurrentGame->GameState().GameId, sizeof(int));
    File.write((char*)&CurrentGame->GameState().Moves, sizeof(int));
    File.write((char*)&CurrentGame->GameState().bWin, sizeof(bool));
    File.write((char*)&CurrentGame->GameState().Time, sizeof(int));
    for (auto& Puzzle : CurrentGame->GameState().PuzzleVector)
    {
        File.write((char*)&Puzzle, sizeof(FPuzzle));
    }
    File.close();
    UpdateScoreFile();
    UpdateGameSaves();
}

void FPlayer::LoadGame(std::string SaveName)
{
    if(CurrentGame)
    {
        SaveGame();
    }
    FGameConfig GameConfig;
    FGameState GameState;

    std::ifstream File;
    File.open(SaveDirPath + "/" + SaveName, std::ios::in);
    File.seekg(0);
    File.read((char*)&GameConfig, sizeof(FGameConfig));
    File.read((char*)&GameState.GameId, sizeof(int));
    File.read((char*)&GameState.Moves, sizeof(int));
    File.read((char*)&GameState.bWin, sizeof(bool));
    File.read((char*)&GameState.Time, sizeof(int));
    for (int var = 0; var < GameConfig.PuzzleNumber(); ++var)
    {
        FPuzzle Puzzle;
        File.read((char*)&Puzzle, sizeof(FPuzzle));
        GameState.PuzzleVector.push_back(Puzzle);
    }
    File.close();

    if(GameConfig.Mode() == EMode::FreeSwap)
    {
        CurrentGame = std::make_unique<FGameFreeSwap>(GameState, GameConfig.Difficulty(), GameConfig.Mode());
    }
    else
    {
        CurrentGame = std::make_unique<FGameEmptySwap>(GameState, GameConfig.Difficulty(), GameConfig.Mode());
    }
}

void FPlayer::UpdateScoreFile()
{
    std::ofstream ScoreFile;
    ScoreFile.open(ScorePath, std::ios::out | std::ofstream::trunc);
    ScoreFile.write((char*)&Score, sizeof(Score));
    ScoreFile.close();
}

void FPlayer::UpdateGameSaves()
{
    GameSaves.clear();
    std::filesystem::path Dir {SaveDirPath};
    for (auto& File : std::filesystem::directory_iterator(Dir))
    {
        GameSaves.emplace_back(std::filesystem::path(File.path()).filename().string());
    }
    std::sort(GameSaves.begin(), GameSaves.end(), [](std::string Save1, std::string Save2)
    {
        return std::stoi(Save1) < std::stoi(Save2);
    });
}
