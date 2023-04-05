#ifndef FGAME_H
#define FGAME_H

#include "gameconfig.h"
#include "puzzle.h"

#include <vector>

struct FGameState
{
    int GameId;
    int Moves;
    bool bWin;
    int Time;
    std::vector<FPuzzle> PuzzleVector;
};

class FGame
{

public:
    int GameId() const;
    int Moves() const;
    bool bWin() const;
    int Time() const;
    const std::vector<FPuzzle>& PuzzleVector() const;
    const FGameState& GameState() const;
    const FGameConfig& GameConfig() const;

protected:
    FGameState GameState_{};
    FGameConfig GameConfig_{};

public:
    FGame(int GameId, EDifficulty Difficulty, EMode Mode);
    FGame(FGameState GameState, EDifficulty Difficulty, EMode Mode);
    virtual ~FGame();

    virtual void OnPuzzleClick(int WidgetId) = 0;
    void UpdateTimer();
    bool IsFinished();

protected:
    bool CheckWin();
    void SwapPuzzlePositions(FPuzzle& A, FPuzzle& B);
    FGridPosition IndexToGridPosition(int index);
    std::vector<int> GetShuffledIdxArray();
    virtual void InitPuzzle() = 0;

private:
    int GridPositionToIndex(const FGridPosition& Position);
};

#endif // FGAME_H
