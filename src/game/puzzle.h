#ifndef PUZZLE_H
#define PUZZLE_H
/** @file */

/*! @struct FGridPosition
 *  @author Piotr Nowak
    @brief Position of a puzzle in grid.
*/
struct FGridPosition
{
    int Row; /**< row index  */
    int Column; /**< column index  */
};

/*! @enum EPuzzleType
 *  @author Piotr Nowak
 *  @brief An enum class describing type of puzzle. Used to differentiate puzzles in "Empty tile swap" game.
*/
enum class EPuzzleType
{
    STANDARD,   /**< Puzzle represents a button. Player can click button to move it to empty space.  */
    EMPTY       /**< Puzzle represents an empty space in grid. Player can move neighbour puzzles to empty space. */
};

/**
 *  @author Piotr Nowak
 *  @brief Represents a single puzzle piece.
 */
class FPuzzle
{
public:

    /**
    * Default constructor
    */
    FPuzzle();

    /**
     * Constructor
     * @param Id puzzle unique identifier.
     * @param GridPosition initial puzzle grid position.
     * @param PuzzleType enum type of puzzle.
     */
    FPuzzle(int Id, FGridPosition GridPosition, EPuzzleType PuzzleType);

    /**
     * Getter
     * @return Current grid position of puzzle
     */
    const FGridPosition& GridPosition() const;

    /**
    * Setter for position of puzzle in grid
    */
    void SetGridPosition(const FGridPosition &NewGridPosition);

    /**
     * Getter
     * @return Puzzle unique identifier used to check if puzzle is on correct position
     */
    int Id() const;

    /**
     * Getter
     * @return Puzzle type
     */
    EPuzzleType PuzzleType() const;

public:
    /**
     * Check if puzzle passed in parameter is on top, left, right or bottom side.
     * @param Puzzle puzzle to check.
     * @return Result of check.
     */
    bool IsNeighbour(const FPuzzle &Puzzle) const;

private:
    FGridPosition GridPosition_{};
    const int Id_{};
    const EPuzzleType PuzzleType_{};
};

#endif // PUZZLE_H
