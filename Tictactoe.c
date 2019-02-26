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
    for (int i = 0; i < 9; i++)
    {
        start->data[i] = square[i];
        printf("%c", start->data[i]);
    }
    start->next = NULL;
    start->prev = NULL;
    return start;
}

node addNode(node head)
{
    node temp, p;
    temp = createNode();    
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

void undoMove(node p)
{
    if(p==NULL || p->prev == NULL)
    {
        printf("Cannot undo any more actions");
    }
    else
    {
        p = p->prev;
        for (int i = 0; i < 9; i++)
        {
            square[i] = p->data[i];
        }
        displayBoard();
        
    }
}

void redoMove(node p)
{
    if (p == NULL || p->next == NULL)
    {
        printf("Cannot redo any more actions");
    }
    else
    {
        p = p->next;
        for (int i = 0; i < 9; i++)
        { 
            square[i] = p->data[i];
        }
        displayBoard();
        
    }
}

int main()
{
    node lastGame;
    lastGame = NULL;
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
                node currentGame;
                currentGame = createNode();
                clearBoard();


                displayBoard();

                while (winner == false)
                {
                    
                    printf("\nPlease enter the square(between 1-9) you'd like to choose, or press Z to undo, X to redo: Player %d \n", player);
                    char selection;
                    bool validInput = false;
                    scanf("%c", &selection);
                    int select = selection;

                    while(validInput == false)
                    {
                        if (select >= 1 && select <= 9 && square[select -1] == '-')
                        {
                            validInput = true;
                        }
                        if (selection == 'z' || selection == 'x')
                        {
                            validInput = true;
                        }
                        else if(!validInput)
                        {
                            printf("Selection was not valid, please try again, selection was: %c\n", selection);
                            scanf("%d", &select);
                        }
                    }
                    
                    if (validInput = true)
                    {
                        if (select == 'x' || select == 'z')
                        {
                            select == 'z' ? undoMove(currentGame) : redoMove(currentGame);
                            select == 'z' ? turncount--: turncount++;         
                        }
                        else
                        {
                            square[select-1] = player==1 ? 'x' : 'o';
                            displayBoard();
                            turncount++;
                            addNode(currentGame);
                            winner = checkWin();
                            if( winner == true)
                            {
                                printf("\nCongratulations! Player %d wins the game!\n", player);
                                lastGame = currentGame;
                            }
                            if(turncount == 9 && winner == false)
                            {
                                printf("\nThe game has ended as a draw\n");
                                winner = true;
                                lastGame = currentGame;
                            }
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
                printList(lastGame);
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