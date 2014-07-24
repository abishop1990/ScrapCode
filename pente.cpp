/* pente.cpp
 * 
 * Coding demo for Brainium involving logic for the game Pente
 *
 * Written By Alan Bishop 7/23/14
 */
 

//  A few assumptions are made here:
//      -The Board type is a 2D Array representing the 19x19 board
//      -There is a Coordinate struct used for the lastCoord and Capture values
//      -The parameter player is an int (1 or 2)
//      -According to the rules the board is 19x19, this is a defined constant


#define BOARD_SIZE 19

struct Coordinate { int x, y, state; };

typedef int Board[BOARD_SIZE][BOARD_SIZE];

struct Captures
{
    Coordinate square;
    Captures * next;
};




//Checks board for if the player has 5 in a row
bool fiveInARow(Board board, int player)
{
    //Basic sanity check, would need to change for more players
    if(player != 1 && player != 2) return false;

    bool searchDown = false, searchRight=false, searchDiagonally=false;
    int currentSquareState;

    //Search each square and the 4 following right, down and the diagonal of the two
    for(int x = 0; x < BOARD_SIZE; ++x)
    {
        for(int y = 0; y < BOARD_SIZE; ++y)
        {
            //Get what's in the square
            currentSquareState = board[x][y];

            //If this square doesn't belong to the player, go to the next one
            if(currentSquareState != player) continue;
        
            //Set variables for searching in loop
            //If these aren't set, we won't look in that direction 
            //(Or else we'll index out of bounds)
            if(x < BOARD_SIZE - 4) searchRight = true;
            if(y < BOARD_SIZE - 4) searchDown = true;
            if(x < BOARD_SIZE - 4 && y < BOARD_SIZE - 4) searchDiagonally = true; 

            //Look at next 4 in all direction
            for(int i = 1; i < 5; ++i)
            {
                //If we aren't searching in any direction, leave the loop
                if(!searchRight && !searchDown && !searchDiagonally) break;
                //Check to the right
                if(searchRight && board[x+i][y] != player) searchRight = false;
                //Check below
                if(searchDown && board[x][y+1] != player) searchDown = false;
                //Check diagonally
                if(searchDiagonally && board[x+i][y+i] != player) searchDiagonally = false;
            }

            //See if we found anything, if so return true
            if(searchRight || searchDown || searchDiagonally) return true;
        }
    }
    return false;
}


//Helper function for getCaptures/Captures linked list
Captures * addCapture(Captures * captures, int x, int y, int state)
{
    //Create a new Captures struct
    Captures * c = new Captures;
    c->square.x = x;
    c->square.y = y;
    c->square.state = state;

    //Find out where to put it
    if(captures == 0)
    {
        captures = c;
    }
    else
    {
        Captures * cur = captures;
        while(cur->next) cur = cur->next;
        cur->next = c;
    }
    
    return captures;
}



//Return all captures to be done based off of lastMove
//I'm doing this as a linked list since it's easy to dynamically add and remove from the ends
Captures * getCaptures(Board board, Coordinate * lastMove)
{
    //Basic sanity check
    if(lastMove == 0 || board == 0) return 0;

    //Get the player that made the last move and the other possible player
    //(We'd need to recode this function if we expanded to 3 or more players)
    int player = 0, otherPlayer;
    switch(lastMove->state)
    {
        case 1: player = 1;  otherPlayer = 2; break;
        case 2: player = 2;  otherPlayer = 1; break;
        default: return 0; //May want to throw an exception here instead
    }
    //Store coords in local variable (For readability)
    int x = lastMove->x;
    int y = lastMove->y;


    Captures * captures = 0;
    //Search board for captures around the last move
    //(We assume that captures from moves before that were already done)
        

    //Check up
    if(y > 2)
    {
        if(board[x][y-3] == player && board[x][y-2] == otherPlayer && board[x][y-1] == otherPlayer) 
        {
            captures = addCapture(captures,x,y-1,otherPlayer);
            captures = addCapture(captures,x,y-2,otherPlayer);
        }
    }

    //Check down
    if(y < BOARD_SIZE - 4) 
    {
        if(board[x][y+1] == otherPlayer && board[x][y+2] == otherPlayer && board[x][y+3] == player)
        {
            captures = addCapture(captures,x,y+1,otherPlayer);
            captures = addCapture(captures,x,y+2,otherPlayer);
        }
    }

    //Check left
    if(x > 2)
    { 
        if(board[x-3][y] == player && board[x-2][y] == otherPlayer && board[x-1][y] == otherPlayer)
        {
            captures = addCapture(captures,x-1,y,otherPlayer);
            captures = addCapture(captures,x-2,y,otherPlayer);
        }
    }
    
    //Check right
    if(y < BOARD_SIZE - 4)
    {
        if(board[x+1][y] == otherPlayer && board[x+2][y] == otherPlayer && board[x+3][y] == player)
        {
            captures = addCapture(captures,x+1,y,otherPlayer);
            captures = addCapture(captures,x+2,y,otherPlayer);
        }
    }


    //Check diagonal up and left
    if(y > 2 && x > 2)
    {
        if(board[x-3][y-3] == player && board[x-2][y-2] == otherPlayer && board[x-1][y-1] == otherPlayer)
        {
            captures = addCapture(captures,x-1,y-1,otherPlayer);
            captures = addCapture(captures,x-2,y-2,otherPlayer);
        }
    }

    //Check diagonal up and right
    if(y > 2 && x < BOARD_SIZE - 4)
    {
        if(board[x+1][y-1] == otherPlayer && board[x+2][y-2] == otherPlayer && board[x+3][y-3] == player)
        {
            captures = addCapture(captures,x+1,y-1,otherPlayer);
            captures = addCapture(captures,x+2,y-2,otherPlayer);
        }
    }

    //Check diagonal down and right
    if(y < BOARD_SIZE - 4 && x < BOARD_SIZE -4)
    {
        if(board[x+1][y+1] == otherPlayer && board[x+2][y+2] == otherPlayer && board[x+3][y+3] == player)
        {
            captures = addCapture(captures,x+1,y+1,otherPlayer);
            captures = addCapture(captures,x+2,y+2,otherPlayer);
        }
    }

    //Check diagonal down and left
    if(y < BOARD_SIZE - 4 && x  > 2)
    {
        if(board[x-1][y+1] == otherPlayer && board[x-2][y+2] == otherPlayer && board[x+3][y+3] == player)
        {
            captures = addCapture(captures,x-1,y+1,otherPlayer);
            captures = addCapture(captures,x-2,y+2,otherPlayer);
        }
    }

    return captures;
}
