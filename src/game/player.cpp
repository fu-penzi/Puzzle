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
    PlayerScores_.AddStartedGame();
    if(CurrentGame_)
    {
        SaveGame();
    }

    if(GameMode == EMode::FreeSwap)
    {
        CurrentGame_ = std::make_unique<FGameFreeSwap>(PlayerScores_.GamesPlayed(), Difficulty, GameMode);
    }
    else
    {
        CurrentGame_ = std::make_unique<FGameEmptySwap>(PlayerScores_.GamesPlayed(), Difficulty, GameMode);
    }

    SaveGame();
}

void FPlayer::SaveGame()
{
    if(!CurrentGame_)
    {
        return;
    }

    const std::string Filename{std::to_string(CurrentGame_->GameId())};
    std::ofstream File;
    File.open(SaveDirPath_ + "/" + Filename, std::ios::out | std::ofstream::trunc);
    File.clear();
    File.write(reinterpret_cast<char*>(const_cast<FGameConfig*>(&CurrentGame_->GameConfig())), sizeof(FGameConfig));
    File.write(reinterpret_cast<char*>(const_cast<int*>(&CurrentGame_->GameState().GameId)), sizeof(int));
    File.write(reinterpret_cast<char*>(const_cast<int*>(&CurrentGame_->GameState().Moves)), sizeof(int));
    File.write(reinterpret_cast<char*>(const_cast<bool*>(&CurrentGame_->GameState().bWin)), sizeof(bool));
    File.write(reinterpret_cast<char*>(const_cast<int*>(&CurrentGame_->GameState().Time)), sizeof(int));
    for (auto& Puzzle : CurrentGame_->GameState().PuzzleVector)
    {
        File.write(reinterpret_cast<char*>(const_cast<FPuzzle*>(&Puzzle)), sizeof(FPuzzle));
    }
    File.close();
    UpdateGameSaves();
}

void FPlayer::FinishGame()
{
    RemoveSave(SaveDirPath_ + "/" + std::to_string(CurrentGame_->GameId()));
    PlayerScores_.SaveScore(CurrentGame_.get());
    Pause_ = true;
}

void FPlayer::LoadGame(std::string SaveName)
{
    Pause_ = false;
    if(CurrentGame_)
    {
        SaveGame();
    }
    FGameConfig GameConfig;
    FGameState GameState;

    std::ifstream File;
    File.open(SaveDirPath_ + "/" + SaveName, std::ios::in);
    File.seekg(0);
    File.read(reinterpret_cast<char*>(&GameConfig), sizeof(FGameConfig));
    File.read(reinterpret_cast<char*>(&GameState.GameId), sizeof(int));
    File.read(reinterpret_cast<char*>(&GameState.Moves), sizeof(int));
    File.read(reinterpret_cast<char*>(&GameState.bWin), sizeof(bool));
    File.read(reinterpret_cast<char*>(&GameState.Time), sizeof(int));
    for (int var = 0; var < GameConfig.PuzzleNumber(); ++var)
    {
        FPuzzle Puzzle;
        File.read(reinterpret_cast<char*>(&Puzzle), sizeof(FPuzzle));
        GameState.PuzzleVector.push_back(Puzzle);
    }
    File.close();

    if(GameConfig.Mode() == EMode::FreeSwap)
    {
        CurrentGame_ = std::make_unique<FGameFreeSwap>(GameState, GameConfig.Difficulty(), GameConfig.Mode());
    }
    else
    {
        CurrentGame_ = std::make_unique<FGameEmptySwap>(GameState, GameConfig.Difficulty(), GameConfig.Mode());
    }
}

bool FPlayer::Pause() const
{
    return Pause_;
}

FGame* FPlayer::CurrentGame()
{
    return CurrentGame_.get();
}

const FPlayerScores& FPlayer::PlayerScores() const
{
    return PlayerScores_;
}

const std::vector<std::string>& FPlayer::GameSaves() const
{
    return GameSaves_;
}

void FPlayer::UpdateGameSaves()
{
    GameSaves_.clear();
    std::filesystem::path Dir {SaveDirPath_};
    for (auto& File : std::filesystem::directory_iterator(Dir))
    {
        GameSaves_.emplace_back(std::filesystem::path(File.path()).filename().string());
    }
    std::sort(GameSaves_.begin(), GameSaves_.end(), [](std::string Save1, std::string Save2)
    {
        return std::stoi(Save1) < std::stoi(Save2);
    });
}

void FPlayer::RemoveSave(std::string Filename)
{
    std::remove(Filename.c_str());
    UpdateGameSaves();
}
