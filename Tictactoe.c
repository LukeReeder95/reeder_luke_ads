#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

bool checkWin();
void displayBoard();
void clearBoard();
char square[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
struct GameState
{
    char data[9];
    struct GameState *next;
    struct GameState *prev;
};

typedef struct GameState *node;

node createNode()
{
    node start;
    start = (node)malloc(sizeof(struct GameState));
    start->next = NULL;
    start->prev = NULL;
    return start;
}

node addNode(node head, char values[9])
{
    node temp, p;
    temp = createNode();
    for(int i = 0; i < 9; i++)
    {
        temp->data[i] = values[i];
    }
    
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = temp;
        temp->prev = p;
    }
    return head;
}

void printList(node p)
{
    if(p == NULL)
    {
        printf("There is not a game stored\n");
    }
    while(p != NULL)
    {
        for(int i = 0; i < 9; i++)
        {
            square[i] = p->data[i];
        }
        displayBoard();        
        p = p->next;
        Sleep(1000);
    }
}

int main()
{
    node currentGame;
    currentGame = createNode();
    node *head = NULL;
    node *current = NULL;
    node *last = NULL;
    while(1)
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

                clearBoard();


                displayBoard();

                while (winner == false)
                {
                    
                    printf("\nPlease enter the square(between 1-9) you'd like to choose Player %d \n", player);
                    int select;
                    bool validInput = false;
                    scanf("%d", &select);

                    while(validInput == false)
                    {
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
                        addNode(currentGame, square);
                        winner = checkWin();
                        if( winner == true)
                        {
                            printf("\nCongratulations! Player %d wins the game!\n", player);
                        }
                        if(turncount == 9 && winner == false)
                        {
                            printf("\nThe game has ended as a draw\n");
                            winner = true;
                        }
                        
                        player==1 ? player++ : player--;
                    }
                }
                break;
            
            case 2:
                printf("Thank you for playing!\n");
                exit(0);
                break;
            
            case 3:
                printf("Printing last game.\n");
                printList(currentGame);
                break;
            
            default:
                printf("The option you have chosen was invalid, please enter a new option.\n");
                break;
        }
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
    for (int i = 0; i < 3; i++)
    {
        if ((square[(i * 3)] == square[(i * 3) + 1] && square[i] == square[(i * 3) + 2] && square[(i * 3)] != '-')  
        ||(square[i] == square[i + 3] && square[i] == square[i + 6] && square[i] != '-'))
            return true;
    }
        if ((square[0] == square[4] && square[4] == square[8] && square[0] != '-')
        || (square[2] == square[4] && square[4] == square[6] && square[2] != '-'))
            return true;
    return false;
}

void clearBoard()
{
    for(int i = 0; i < 9; i++)
    {
        square[i] = '-';
    }
    
}