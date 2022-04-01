#include "../Headers/Tour.h"

int main()
{
    // desires board size to run a knights tour on
    int ROWS = 8;
    int COLS = 8;
    int SIZE = ROWS * COLS;

    // knights starting location
    int STARTX = 0;
    int STARTY = 0;

    // instantiate Knight's Tour
    Tour knightsTour(ROWS, COLS, SIZE, STARTX, STARTY);

    // Tour loop
    while(knightsTour.getValidTour() == false)
    {
        knightsTour.solveTour();
    }
    
    return 0;
}