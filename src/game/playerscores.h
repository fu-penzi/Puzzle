#ifndef SCORE_H
#define SCORE_H

#include "game.h"
#include "gameconfig.h"

#include <string>
#include <vector>
/** @file */

/*! @struct FScore
    @author Piotr Nowak
    @brief Structure representing a score of a finished game.
*/
struct FScore
{
    int GameId; /**< Game unique identifier.  */
    int RemainingTime; /**< Remaining time to finish game.  */
    int Moves; /**< Number of moves player made.  */
    bool bWin; /**< If player finished game before time run out. */
    EDifficulty Difficulty; /**< Game difficulty.  */
    EMode GameMode; /**< Game mode.  */
};

/**
 *  @author Piotr Nowak
 *  @brief Saves and loads player scores.
 */
class FPlayerScores
{
public:
    /**
     * Constructor
     * @param ScorePath path of file with player scores.
     */
    FPlayerScores(std::string ScorePath);

    /**
     * Getter
     * @return Total number of games player played.
     */
    int GamesPlayed() const;

    /**
     * Getter
     * @return Number of games player won.
     */
    int GamesWon() const;

    /**
     * Getter
     * @return Number of games player lost.
     */
    int GamesLost() const;

    /**
     * Getter
     * @return Vector of scores for games player finished.
     */
    const std::vector<FScore>& Scores() const;

public:

    /**
     * Increase number of total games played.
     */
    void AddStartedGame();

    /**
     * Save finished game score to file.
     * @param Game finished game used to create new score.
     */
    void SaveScore(FGame* Game);

private:
    int GamesPlayed_ = 0;
    int GamesWon_ = 0;
    int GamesLost_ = 0;
    std::vector<FScore> Scores_;
    const std::string ScorePath_;

private:
    void UpdateScoreFile();
    void LoadScoreFile();
};

#endif // SCORE_H
