#include <iostream>
#include <stdlib.h>
#include <vector>

using std::cout;
using std::vector;
using std::endl;

//Constants
#define MAX 8

//function prototypes
void initialization(int (&state)[8]);
int conflictCounting(int (&state)[8],int,int);
bool IsFinalState(int (&state)[8]);
void Searching(int (&state)[8]);

int main()
{
    //seed to produce same random values
    srand(2);

    //Declare variables
    int S[MAX] = {-1,-1,-1,-1,-1,-1,-1,-1};

    //select a random value for the first column
    S[0] = rand() % MAX;

    //initialize the board
    initialization(S);

    //print the status of the queens
    cout << "Status of Queens" << endl;
    cout << endl;

    for(int i = 0; i < MAX; i++)
    {
        cout << "Column: " << i << " Row: " << S[i] << endl;
    }

    cout << endl;

    //Use Min-Conflict on the queens to find solution
    Searching(S);

}

//put the queens on the board
void initialization(int (&state)[8])
{
    cout << "Initializing" << endl;
    cout << endl;

    //declare variables
    vector<int> min_conflicts;
    int minimum = 9;
    int conflicts;

    //go through the columns
    for(int column = 1;column < MAX; column++)
    {
        //go through the rows of each column
        for(int rows = 0; rows < MAX; rows++)
        {
            //get the number of conflicts of a square
            conflicts = conflictCounting(state, rows,column);

            //check if conflict is the minimum
            if(conflicts < minimum)
            {
                //check vector to see if it is empty
                if(!min_conflicts.empty())
                {
                    min_conflicts.clear();
                }

                minimum = conflicts;
                min_conflicts.push_back(rows);
            }

            //conflict is already a minimum
            if(conflicts == minimum)
            {
                min_conflicts.push_back(rows);
            }

        }


        //there is only one row to choose from
        if(min_conflicts.size() == 1)
        {
            state[column] = min_conflicts.at(0);
        }
        else
        {
            state[column] = min_conflicts.at(rand() % min_conflicts.size());
        }

        //reset values for next column
        min_conflicts.clear();
        minimum = 9;
    }
}

//count the conflict of the square
int conflictCounting(int (&state)[8],int row,int column)
{
    int diagonalSquare = row;
    int conflict = 0;

    //check to see conflicts in row
    for(int r = 0;r < MAX; r++)
    {
        //there is a queen placed on the board
        if(state[r] != -1)
        {
            //ignore queen in column
            if(column != r)
            {
                //check if there is a queen in the same row
                if(state[r] == row)
                {
                    conflict++;
                }
            }

        }

    }

    //check top right diagonal
    for(int i = column+1; i < MAX;i++)
    {
        diagonalSquare -= 1;

        //there is a queen placed in a column
        if(state[i] != -1)
        {
            //there is a queen in the top right square
            if(state[i] == diagonalSquare)
            {
                conflict++;
            }
        }
    }

    //reset variable value
    diagonalSquare = row;


    //check bottom right diagonal
    for(int j = column+1; j < MAX; j++)
    {
        diagonalSquare += 1;

        //there is a queen placed in a column
        if(state[j] != -1)
        {
             //there is a queen in the bottom right square
            if(state[j] == diagonalSquare)
            {
                conflict++;
            }
        }
    }

     //reset variable value
    diagonalSquare = row;


    //check bottom left diagonal
    for(int k = column-1; k >= 0; k--)
    {
        diagonalSquare += 1;

        //there is a queen placed in a column
        if(state[k] != -1)
        {
             //there is a queen in the bottom left square
            if(state[k] == diagonalSquare)
            {
                conflict++;
            }
        }
    }

    //reset variable value
    diagonalSquare = row;

     //check top left diagonal
    for(int l = column-1; l >= 0; l--)
    {
        diagonalSquare -= 1;

        //there is a queen placed in a column
        if(state[l] != -1)
        {
             //there is a queen in the top left square
            if(state[l] == diagonalSquare)
            {
                conflict++;
            }
        }
    }


    return conflict;
}

//Check if the final state of the board has been reached
bool IsFinalState(int (&state)[8])
{
    int numOfConflicts;

    //check the states of the queens
    for(int i = 0;i < MAX; i++)
    {
        //get the queen's conflict
        numOfConflicts = conflictCounting(state, state[i],i);

        //there is a queen that has a conflict
        if(numOfConflicts != 0)
        {
            return false;
        }

    }

    //There are no conflicting queens
    return true;
}

//Search for solution using Min-Conflict to 8-Queens Problem
void Searching(int (&state)[8])
{
    //declare variables
    bool isSearching = true;
    vector<int> conflictSquare;
    int minimum = 9;
    int conflicts;
    int column;
    int moves = 0;

    //Search until you find solution
    while(isSearching)
    {
        //Need to search further
         if(!IsFinalState(state))
        {
            for(int i = 0; i < MAX; i++)
            {
                //get the number of conflicts of a square
                conflicts = conflictCounting(state, state[i], i);

                if(conflicts != 0)
                {
                    conflictSquare.push_back(i);
                }

            }

               //there is only one column to choose from
                if(conflictSquare.size() == 1)
                {
                    column = conflictSquare.at(0);
                }
                else
                {
                    column = conflictSquare.at(rand() % conflictSquare.size());
                }

                //let user know what queen is selected
                cout << "I am selecting Queen at column: " << column << endl;
                cout << endl;

                //reset values
                conflictSquare.clear();


                //Check that specific column
                for(int j = 0;j< MAX;j++)
                {
                    conflicts = conflictCounting(state,j,column);

                     //check if conflict is the minimum
                    if(conflicts < minimum)
                    {
                        //check vector to see if it is empty
                        if(!conflictSquare.empty())
                        {
                            conflictSquare.clear();
                        }

                        minimum = conflicts;
                        conflictSquare.push_back(j);
                    }

                    //conflict is already a minimum
                    if(conflicts == minimum)
                    {
                        conflictSquare.push_back(j);
                    }

                }

                //there is only one row to choose from
                if(conflictSquare.size() == 1)
                {
                    state[column] = conflictSquare.at(0);
                }
                else
                {
                    state[column] = conflictSquare.at(rand() % conflictSquare.size());
                }

                //Status update of the state
                cout << "Queen of column: " << column << " is moving to row: " << state[column] << endl;
                cout << endl;

                moves++;

                //reset values
                conflictSquare.clear();
                minimum = 9;
        }
        else
        {
            isSearching = false;

            cout << "Queen Problem Solved" << endl;
            cout << endl;

            for(int k = 0; k < MAX; k++)
            {
                cout << "Column: " << k << " Row: " << state[k] << endl;
            }

            cout << endl;
            cout << "It took " << moves << " moves to solve the 8x8 queen problem";
        }
    }

}


