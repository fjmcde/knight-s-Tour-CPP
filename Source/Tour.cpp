#pragma once
#include "../Headers/Tour.h"
#include <iostream>

Tour::Tour(int numRows, int numCols, int boardSize, int startX, int startY)
{
    // initialize board specifications
    rows_ = numRows;
    cols_ = numCols;
    size_ = boardSize;

    // initialize Tour data
    moveNum_ = 0;
    startIndex_ = startX + (startY * cols_);
    endIndex_ = NULL;
    validTour_ = false;

    // initialize the board
    board_.resize(size_);

    // initialize knight and space pointers
    knight_ = new Space(moveNum_, startIndex_);

    // set the knight on the board
    board_.at(startIndex_) = knight_;

    // initialie legalMoves vector
    legalMoves_ = {
        {2, -1}, {1, -2},   // right-up
        {-2, -1}, {-1, -2}, // left-up
        {-2, 1}, {-1, 2},   // left-down
        {2, 1}, {1, 2}    // right-down
    };
}

Tour::~Tour()
{
    delete knight_;
}

void Tour::move()
{
    // grab an integer pair from the legalMoves_ vector;
    // split into individual variables for readablity
    int moveIndex = knight_->legalMoveIndex_;
    int x = legalMoves_[knight_->legalMoveIndex_].first;
    int y = legalMoves_[knight_->legalMoveIndex_].second;

    // calculate the index of the next move
    int moveTo = knight_->vectorIndex_ + x + (y * cols_);

    // if move is valid; move to the proper space
    if(checkValidMove(moveTo, x, y) == true)
    {
        updateSpaces(moveTo);
    }
    else
    {
        knight_->legalMoveIndex_++;
    }
    
    // if all 8 legal moves have been attempted; backtrack to previous space
    if(knight_->legalMoveIndex_ == legalMoves_.size())
    {
        // if the root is reached and no valid moves remain; 
        // the tour is over and a valid knight's tour isn't possible
        // for the given configuation.
        if(knight_->previousSpace_ == nullptr) validTour_ = false;
        
        // otherwise simply backtrack
        backtrack();
    }

    isSolved();
}

bool Tour::checkValidMove(int moveTo, int x, int y)
{
    // calculate variables for bounds checking.
    //endRow is a float to avoid integer division rounding a negative 
    // number > -1 to 0
    int startRow = knight_->vectorIndex_ / rows_;
    float actualEndRow = (float)moveTo / (float)rows_;
    int expectedEndRow = startRow + y;
    

    // validMove_ is set to false initially because in a brute-force
    // algorithm, the majority of the attempted moves are false.
    // it also simplifies the conditional statements by avoiding three
    // else statements
    validMove_ = false;

    // important to remember that this is a 1-D representation
    // of a 2-D board. this comes with it's own set of checks
    // to ensure a move is technically valid.

    // check upper and lower bounds of desired space
    // a move cannot move below index 0 or above index
    // size_ - 1 of the board_ vector
    if((moveTo > -1) && (moveTo < size_))
    {
        // check for row overflow
        // a move could calculate a valid index (one-dimensionally
        // speaking), but depending on the starting position, the 
        //index may be out-of-bounds given the row and column 
        //constraints (two-dimensionally speaking)
        //if(endRow >= 0)
        if(actualEndRow >= 0)
        {
            //if((int)endRow == startRow + y)
            if((int)actualEndRow == expectedEndRow)
            {
                // check if space has been visited
                // we can only visit each space once in a knight's tour
                if(board_[moveTo] == NULL)
                {
                    validMove_ = true;
                }
            }
        }
    }

    return validMove_;    
}

void Tour::updateSpaces(int moveTo)
{
    // explicitly for readiblity purposes when passed
    // into Space constructor
    moveNum_++;
    bool visited = true;
    int moveIndex = 0;

    // create a new space (object; not pointer) and add it to the board 
    //nvector at the desired index.
    Space* newSpace =  new Space(moveNum_, moveTo, visited, moveIndex, knight_);
    board_.at(moveTo) = newSpace;

    // temp pointer for swap
    Space* temp = knight_;

    // update pointers
    knight_->nextSpace_ = board_.at(moveTo);
    knight_ = board_.at(moveTo);
    knight_->previousSpace_ = temp;
    knight_->nextSpace_ = nullptr;
}

void Tour::backtrack()
{
    moveNum_--;
    Space* previousSpace = knight_->previousSpace_;

    // moving from...
    int oldIndex = knight_->vectorIndex_;

    // update knight
    knight_ = previousSpace;
    knight_->nextSpace_ = nullptr;
    knight_->moveNum_ = moveNum_;
    knight_->legalMoveIndex_++;

    // erase element of the board vector at the previous 
    // location (prior to the above update) of the knight
    board_.at(oldIndex) = NULL;

    // recursively backtrack if we've exhausted all legal moves
    // at the newly backtracked space
    if(knight_->legalMoveIndex_ == legalMoves_.size())
    {
        backtrack();
    }
}

void Tour::isSolved()
{
    if(moveNum_ == size_ - 1)
    {
        validTour_ = true;
        endIndex_ = knight_->vectorIndex_;

        isClosed();

        return;
    }
}

void Tour::isClosed()
{
    for(int i = 0; i < 8; i++)
    {
        int x = legalMoves_[i].first;
        int y = legalMoves_[i].second;
        int moveTo = endIndex_ + x + (y + rows_);

        if(startIndex_ == endIndex_)
        {
            openTour_ = false;
            return;
        }
        else
        {
            openTour_ = true;
        }
    }
}

void Tour::solveTour()
{
    while(validTour_ == false)
    {
        move();
    }

    printTour();

    return;
}

void Tour::printTour()
{
    for(int i = 0; i < rows_; i++)
    {
        for(int j = 0; j < cols_; j++)
        {
            std::cout << board_[i * cols_ + j]->moveNum_ << "\t";
        }

        std::cout << "\n";
    }
}