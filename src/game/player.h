#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "playerscores.h"

#include <memory>
#include <string>
#include <vector>


/**
 *  @author Piotr Nowak
 *  @brief Saves and loads player scores.
 */
class FPlayer
{
public:
    /**
     *  Default constructor. Initializes directories and finds all save files.
     */
    FPlayer();

    /**
     *  Getter
     *  @return player scores
     */
    const FPlayerScores& PlayerScores() const;

    /**
     *  Getter
     *  @return vector of player game save file names
     */
    const std::vector<std::string>& GameSaves() const;

    /**
     *  Getter
     *  @return is current game paused
     */
    bool Pause() const;


    /**
     *  Getter
     *  @return pointer to current game
     */
    FGame* CurrentGame();

public:

    /**
     *  Start new game.
     *  @param Difficulty new game difficulty
     *  @param GameMode new game mode
     */
    void NewGame(EDifficulty Difficulty, EMode GameMode);

    /**
     *  Save current game state to file.
     */
    void SaveGame();

    /**
     *  Finish current game and create new score
     */
    void FinishGame();

    /**
     *  Loads game from save file.
     *  @param SaveName name of save file to load
     */
    void LoadGame(std::string SaveName);

private:
    std::unique_ptr<FGame> CurrentGame_{};
    FPlayerScores PlayerScores_{"Profiles/Player/Score"};
    std::vector<std::string> GameSaves_{};
    bool Pause_{};

    const std::string ProfilesDirPath_ {"Profiles"};
    const std::string ProfilePath_ {ProfilesDirPath_ + "/Player"};
    const std::string SaveDirPath_ {ProfilePath_ + "/Saves"};

private:
    void UpdateGameSaves();
    void RemoveSave(std::string Filename);
};

#endif // PLAYER_H
