#pragma once
#include <vector>

struct Space
{
public:
    // Space data
    int moveNum_;
    int vectorIndex_;
    int legalMoveIndex_;
    bool visited_;

    // Pointers
    Space* previousSpace_;
    Space* nextSpace_;

    // constructor
    Space(int moveNum = -1, int vectorIndex = 0, bool visited = true,
        int moveIndex = 0, Space* previousSpace = nullptr,
        Space* nextSpace = nullptr)
    {
        moveNum_ = moveNum;
        vectorIndex_ = vectorIndex;
        legalMoveIndex_ = moveIndex;
        visited_ = visited;
        previousSpace_ = previousSpace;
        nextSpace_ = nextSpace;
    }
};

class Tour
{
    private:
    // Board data
        int rows_;
        int cols_;
        int size_;
    
    // Tour data
        int moveNum_;
        int startIndex_;
        int endIndex_;
    
    // knight
        Space* knight_;

    
    // Tour structures
        std::vector<Space*> board_;
        std::vector<std::pair<int, int>> legalMoves_;

    // Tour flags
        bool validMove_;
        bool validTour_;
        bool openTour_;
    
    // Private Member functions
        void move();
        bool checkValidMove(int moveTo, int x, int y);
        void updateSpaces(int moveTo);
        void backtrack();
        void printTour();
        void isSolved();
        void isClosed();

    public:
        Tour(int numRows, int numCols, int boardSize, int startX, int startY);
        ~Tour();

    // public membet functions
        void solveTour();
};