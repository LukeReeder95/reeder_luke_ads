#include <stdio.h>
#include <stdbool.h>

bool checkWin();
void displayBoard();
char square[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
struct GameState
{
    char square[9];
    struct GameState *next;
    struct GameState *prev;
};

typedef struct GameState *node;

int main()
{
    
    
    printf("Please select a choice from the following: 1 - Play game   2 - Exit\n");
    int choice;
    scanf("%d", &choice);


    switch(choice)
    {
        case 1:
            int turncount = 0;
            bool winner = false;
            int player = 1;
            node createNode()
            {
                node start;
                start = (node)malloc(sizeof(struct GameState));
                start->next = NULL;
                start->prev = NULL;
            }

            displayBoard();

            while (winner == false)
            {
                
                printf("\nPlease enter the square(between 1-9) you'd like to choose Player %d \n", player);
                int select;
                bool validInput = false;
                scanf("%d", &select);

                while(validInput == false)
                {
                    // && square[select] != '-'
                    if (select >= 1 && select <= 9 && square[select -1] == '-')
                    {
                        validInput = true;
                    }
                    else
                    {
                        printf("Selection was not valid, please try again\n");
                        scanf("%d", &select);
                    }
                }
                
                if (validInput = true)
                {
                    if (player == 1)
                    {
                        square[select-1] = 'x';
                    }
                    else
                    {
                        square[select-1] = 'o';
                    }
                    displayBoard();
                    turncount++;
                    winner = checkWin();
                    if( winner == true)
                    {
                        printf("\nCongratulations! Player %d wins the game!", player);
                    }
                    if(turncount == 9 && winner == false)
                    {
                        printf("\nThe game has ended as a draw");
                        return 0;
                    }
                    
                    player==1 ? player++ : player--;
                }
            }
        case 2:
            printf("Thank you for playing!");
            return 0;

    }

    return 0;
}

void displayBoard()
{
    system("CLS");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", square[0], square[1], square[2]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", square[3], square[4], square[5]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", square[6], square[7], square[8]);
    printf("   |   |   \n");
}

bool checkWin()
{
    if(square[0] == square[1] && square[1] == square[2] && square[0] != '-')
        return true;
    if (square[3] == square[4] && square[4] == square[5] && square[3] != '-')
        return true;
    if (square[6] == square[7] && square[7] == square[8] && square[6] != '-')
        return true;
    if (square[0] == square[3] && square[3] == square[6] && square[0] != '-')
        return true;
    if (square[1] == square[4] && square[4] == square[7] && square[1] != '-')
        return true;
    if (square[2] == square[5] && square[5] == square[8] && square[2] != '-')
        return true;
    if (square[0] == square[4] && square[4] == square[8] && square[0] != '-')
        return true;
    if (square[2] == square[4] && square[4] == square[6] && square[2] != '-')
        return true;
    return false;
}