#include <stdio.h>
#include <stdbool.h>

bool checkWin();
void displayBoard();
char square[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

int main()
{
    bool winner = false;
    int player = 1;
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
                player++;
            }
            else
            {
                square[select-1] = 'o';
                player--;
            }
            displayBoard();
            winner = checkWin();
            if( winner == true)
            {
                if(player == 1)
                {
                    player++;
                }
                else
                {
                    player--;
                }
            }
        }
    }

    printf("\nCongratulations! Player %d wins the game!", player); 
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