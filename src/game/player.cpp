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
    mkdir(ProfilesDirPath_.c_str());
    mkdir(ProfilePath_.c_str());
    mkdir(SaveDirPath_.c_str());
    UpdateGameSaves();
}

void FPlayer::NewGame(EDifficulty Difficulty, EMode GameMode)
{
    Pause_ = false;
    PlayerScores.AddStartedGame();
    if(CurrentGame)
    {
        SaveGame();
    }

    if(GameMode == EMode::FreeSwap)
    {
        CurrentGame = std::make_unique<FGameFreeSwap>(PlayerScores.GamesPlayed(), Difficulty, GameMode);
    }
    else
    {
        CurrentGame = std::make_unique<FGameEmptySwap>(PlayerScores.GamesPlayed(), Difficulty, GameMode);
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
    File.open(SaveDirPath_ + "/" + Filename, std::ios::out | std::ofstream::trunc);
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
    UpdateGameSaves();
}

void FPlayer::FinishGame()
{
    RemoveSave(SaveDirPath_ + "/" + std::to_string(CurrentGame->GameId()));
    PlayerScores.SaveScore(CurrentGame.get());
    Pause_ = true;
}

void FPlayer::LoadGame(std::string SaveName)
{
    Pause_ = false;
    if(CurrentGame)
    {
        SaveGame();
    }
    FGameConfig GameConfig;
    FGameState GameState;

    std::ifstream File;
    File.open(SaveDirPath_ + "/" + SaveName, std::ios::in);
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

bool FPlayer::Pause() const
{
    return Pause_;
}

void FPlayer::UpdateGameSaves()
{
    GameSaves.clear();
    std::filesystem::path Dir {SaveDirPath_};
    for (auto& File : std::filesystem::directory_iterator(Dir))
    {
        GameSaves.emplace_back(std::filesystem::path(File.path()).filename().string());
    }
    std::sort(GameSaves.begin(), GameSaves.end(), [](std::string Save1, std::string Save2)
    {
        return std::stoi(Save1) < std::stoi(Save2);
    });
}

void FPlayer::RemoveSave(std::string Filename)
{
    std::remove(Filename.c_str());
    UpdateGameSaves();
}
