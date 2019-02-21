#include <stdio.h>
#include <stdbool.h>

void displayBoard();
char square[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
int main()
{
    int player = 1;
    displayBoard();
    do
    {
        printf("\nPlease enter the square you'd like to choose Player %d \n", player);
        int select;
        bool validInput = false;
        scanf("%d", &select);

        while(validInput == false)
        {
            // && square[select] != '-'
            if (select >= 0 && select <= 8 && square[select] == '-')
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
                square[select] = 'x';
                displayBoard();
                player++;
            }
            else
            {
                square[select] = 'o';
                displayBoard();
                player--;
            }
        }
    }
    while(0 != 1);
    
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