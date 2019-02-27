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

//struct StartGame
// {
//     int gameID;
//     node gameStart;
//     struct StartGame *next;
// };
// typedef struct StartGame *GameNode;

// GameNode createGameNode(int ID, node head)
// {
//     GameNode start;
//     start = (GameNode)malloc(sizeof(struct StartGame));
//     start->gameID = ID;
//     start->gameStart = head;
//     start->next = NULL;
// }

// GameNode addGameNode(int ID, GameNode head)
// {
//     GameNode temp, p;
//     temp = createGameNode(ID, head);
//     if(head == NULL)
//     {
//         head = temp;
//     }
//     else
//     {
//         p = head;
//         while(p->next != NULL)
//         {
//             p = p->next;
//         }
//         p->next = temp;
//     }
//     return p;
// }

node createNode()
{
    node start;
    start = (node)malloc(sizeof(struct GameState));
    for (int i = 0; i < 9; i++)
    {
        start->data[i] = square[i];
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
    return temp;
}

void printList(node p)
{
    if(p == NULL)
    {
        printf("There is not a game stored\n");
    }
    else
    {
        while (p->prev !=NULL)
        {
            p = p->prev;
        }
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

node undoMove(node p)
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
    return p;
}

node redoMove(node p)
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
    return p;
}

int main()
{
    node lastGame;
    lastGame = NULL;
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

                while (!winner)
                {
                    
                    printf("\nPlease enter the square(between 1-9) you'd like to choose, or 0 for options: Player %d \n", player);
                    bool validInput = false;
                    int select;
                    scanf("%d", &select);

                    while(!validInput)
                    {
                        
                        if ((select >= 1 && select <= 9 && square[select -1] == '-') || select == 0)
                        {
                            validInput = true;
                            break;
                        }
                        else
                        {
                            printf("Selection was not valid, please try again, selection was: %d\n", select);
                            scanf("%d", &select);
                        }
                    }
                    
                    if (validInput = true)
                    {
                        if (select == 0)
                        {
                            printf("Press 1 to undo your last move, 2 to redo, or 3 to exit\n");
                            scanf("%d", &select);
                            if(select == 1 || select == 2)
                            {
                                currentGame = select==1 ? undoMove(currentGame) : redoMove(currentGame);
                                player == 1 ? player++ : player--;
                                select == 1 ? turncount--: turncount++;
                            }
                            else
                            {
                                printf("Game ending early\n");
                                winner = true;
                                lastGame = currentGame;
                                break;
                            }
                            
                        }
                        else
                        {
                            square[select-1] = player==1 ? 'x' : 'o';
                            displayBoard();
                            turncount++;
                            currentGame = addNode(currentGame);
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