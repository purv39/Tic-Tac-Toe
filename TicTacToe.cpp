/*
* Project       :   Tic Tac Toe
* Programmer    :   Purv
* First Version :   27/12/2020
*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>




void getPreGameInfo(int* totalRounds, struct Player* p1, struct Player* p2);
void game(int* currentRound, int totalRounds, struct Player* p1, struct Player* p2);
int checkDrawRound(char place[], int placeLength);
void hud(const struct Player* p1, const struct Player* p2, int currentRound, char array[]);
void grid(char spot[]);
int inGameInput(const struct Player* p1, const struct Player* p2, char place[], int currentPlayer);
int roundComplete(char spots[]);
int seriesWinner(int score1, int score2);
int checkInvalidRange(int number, int lowerLimit, int upperLimit);
int preventOverwriting(int inputNumber, char place[]);
int getNum(void);
void clearNewLine(char string[]);




struct Player
{
    int score;
    char icon;
    char name[121];
};





#pragma warning(disable: 4996)
int main(void)
{

    int totalRounds = 0;
    struct Player p1 = { 0, ' ', "" };
    struct Player p2 = { 0, ' ', "" };
    int p1Score = 0;
    int p2Score = 0;

    char p1Icon = ' ';
    char p2Icon = ' ';
    char p1Name[121] = "";
    char p2Name[121] = "";

    int startRound = 0;

    getPreGameInfo(&totalRounds, &p1, &p2);

    game(&startRound, totalRounds, &p1, &p2);

    system("cls");

    printf("\t\t      Final Score: \n");
    printf("\n\n%s\t:\t%i\t|\t%s\t:\t%i\n\n\n\n", p1.name, p1.score, p2.name, p2.score);

    int winner = seriesWinner(p1.score, p2.score);

    if (winner == 1)
    {
        printf("\t\tThe winner of the series is %s!!", p1.name);
    }
    else if (winner == 2)
    {
        printf("\t\tThe winner of the series is %s!!", p2.name);
    }
    else
    {
        char recordOption[121] = "";
        char option;
        while (1)
        {
            printf("Do you wish to continue?(Y/N): ");

            fgets(recordOption, 121, stdin);

            if (sscanf(recordOption, "%c", &option) != 1)
            {
                continue;
            };

            if (option == 'Y' || option == 'y' || option == 'N' || option == 'n')
            {
                break;
            }
        }

        if (option == 'Y' || option == 'y')
        {
            game(&startRound, totalRounds + 1, &p1, &p2);

            system("cls");
            printf("\t\t      Final Score: \n");
            printf("\n\n%s\t:\t%i\t|\t%s\t:\t%i\n\n\n\n", p1.name, p1.score, p2.name, p2.score);

            int winner = seriesWinner(p1.score, p2.score);

            if (winner == 1)
            {
                printf("\t\tThe winner of the series is %s!!", p1.name);
            }
            else if (winner == 2)
            {
                printf("\t\tThe winner of the series is %s!!", p2.name);
            }

        }
        else
        {
            printf("\t\t      Final Score: \n");
            printf("\n\n%s\t:\t%i\t|\t%s\t:\t%i\n\n\n\n", p1.name, p1.score, p2.name, p2.score);

            int winner = seriesWinner(p1.score, p2.score);

            printf("\t\tThe match is draw!!");
        }

    }

}








/*
* Function      :   getPreGameInfo()
* Description   :   Gets the total rounds to play, player 1 name, player 1 icon, player 2 name and player 2 icon.
* Return Values :   None
*/

void getPreGameInfo(int* totalRounds, struct Player* p1, struct Player* p2)
{
    char record[121] = "";

    while (1)
    {
        printf("Total rounds: ");

        *totalRounds = getNum();

        if (*totalRounds != -1)
        {
            break;
        }

    }

    printf("\n\nEnter Player 1 name: ");
    fgets(p1->name, 121, stdin);
    clearNewLine(p1->name);

    while (1)
    {
        printf("Player 1 symbol: ");

        fgets(record, 121, stdin);
        if (sscanf(record, "%c",&(p1->icon)) == 1 && isalpha(p1->icon) != 0)
        {
            break;
        }
    }

    printf("\nEnter Player 2 name: ");
    fgets(p2->name, 121, stdin);
    clearNewLine(p2->name);

    while (1)
    {
        printf("Player 2 symbol: ");

        fgets(record, 121, stdin);
        if (sscanf(record, "%c", &(p2->icon)) == 1 && isalpha(p2->icon) != 0)
        {
            break;
        }
    }
}







/*
* Function      :   game()
* Description   :   Handles the overall game functionality, keeps track of player scores and displays each round winner.
* Return Values :   None
*/

void game(int* currentRound, int totalRounds, struct Player* p1, struct Player* p2)
{

    while (*currentRound < totalRounds)
    {

        char place[10] = { ' ', ' ',' ',' ',' ',' ',' ',' ',' ', ' ' };
        int currentPlayer = 2;

        do
        {
            if (checkDrawRound(place, 10) == 1)
            {
                printf("Restarting the round!!\n\n");
                printf("Press enter to continue...");
                getch();
            };

            hud(p1, p2, *currentRound, place);

            currentPlayer = inGameInput(p1, p2, place, currentPlayer);

        } while (roundComplete(place) == 0);

        system("cls");

        if (currentPlayer == 1)
        {
            (p1->score)++;
        }
        else
        {
            (p2->score)++;
        }

        printf("\t\t      Round %i Complete.\n\n", *currentRound + 1);

        if (seriesWinner(p1->score, p2->score) == 1)
        {
            printf("\t\tWinner of Round %i is %s!!\n", *currentRound + 1, p1->name);
        }
        else
        {
            printf("\t\tWinner of Round %i is %s!!\n", *currentRound + 1, p2->name);
        }

        printf("\n\n%s\t:\t%i\t|\t%s\t:\t%i\n\n\n\n", p1->name, p1->score, p2->name, p2->score);

        printf("Press Enter to continue...");

        getch();

        (*currentRound)++;
    }
}






/*
* Function      :   checkDrawRound()
* Description   :   Checks if there is no possible further movement possible and the round is draw and restarts the round.
* Return Values :   Returns 1 if draw else returns 0.
*/

int checkDrawRound(char place[], int placeLength)
{
    int emptySpaces = 0;
    for (int counter = 1; counter < placeLength; counter++)
    {
        if (place[counter] == ' ')
        {
            emptySpaces++;
        }

    }

    if (emptySpaces == 0)
    {
        for (int counter = 1; counter < placeLength; counter++)
        {
            place[counter] = ' ';
        }
        return 1;
    }
    else
    {
        return 0;
    }
}








/*
* Function      :   hud()
* Description   :   Displays the round number and current score.
* Return Values :   None
*/

void hud(const struct Player* p1, const struct Player* p2, int currentRound, char array[])
{
    system("cls");

    printf("\t\t      Round %i\n\n", currentRound + 1);
    printf("\n\n%s\t:\t%i\t|\t%s\t:\t%i\n\n\n\n", p1->name, p1->score, p2->name, p2->score);

    grid(array);
}







/*
* Function      :   grid()
* Description   :   Displays the grid.
* Return Values :   None.
*/

void grid(char spot[])
{
    printf("\t    \t|  \t|     \n");
    printf("\t    %c\t|   %c\t|  %c\n", spot[1], spot[2], spot[3]);
    printf("\t  ______|_______|______\n");
    printf("\t     \t|  \t|     \n");
    printf("\t    %c\t|   %c\t|  %c\n", spot[4], spot[5], spot[6]);
    printf("\t  ______|_______|______\n");
    printf("\t     \t|  \t|     \n");
    printf("\t    %c\t|   %c\t|  %c\n", spot[7], spot[8], spot[9]);
    printf("\t     \t|  \t|     \n");
}











/*
* Function      :   inGameInput()
* Description   :   Gets the number of block in the grid in which the player wishes to fill his icon.
* Return Values :   Returns the number of the last player that entered input.
*/

int inGameInput(const struct Player* p1, const struct Player* p2, char place[], int currentPlayer)
{
    int p1Input = 0;
    int p2Input = 0;

    if (currentPlayer == 2)
    {
        currentPlayer = 1;

        while (true)
        {
            printf("\n\n%s's turn: ", p1->name);
            p1Input = getNum();

            if ((p1Input != -1) && (checkInvalidRange(p1Input, 1, 10) == 0) && (preventOverwriting(p1Input, place) == 0))
            {
                break;
            }
        }

        place[p1Input] = p1->icon;

    }
    else
    {
        currentPlayer = 2;

        while (true)
        {
            printf("\n\n%s's turn: ", p2->name);
            p2Input = getNum();
            if ((p2Input != -1) && (checkInvalidRange(p2Input, 1, 10) == 0) && (preventOverwriting(p2Input, place) == 0))
            {
                break;
            }
        }
        place[p2Input] = p2->icon;
    }

    return currentPlayer;
}






/*
* Function      :   roundComplete()
* Description   :   Checks if a player succeeded in placing 3 of their icon in a diagonal, horizontal or vertical row.
* Return Values :   Returns 1 if there is a winner otherwise returns 0.
*/

int roundComplete(char spots[])
{
    /* Checking horizantal lines */
    int place = 1;
    while (place < 10)
    {

        if (((spots[place] == spots[place + 1]) && (spots[place + 1] == spots[place + 2])))
        {
            if (spots[place] != ' ' && spots[place + 1] != ' ' && spots[place + 2] != ' ')
            {
                return 1;
            }

        }
        place += 3;
    }

    /* Checking vertical lines */
    place = 1;
    while (place < 4)
    {
        if ((spots[place] == spots[place + 3]) && (spots[place + 3] == spots[place + 6]))
        {

            if (spots[place] != ' ' && spots[place + 3] != ' ' && spots[place + 6] != ' ')
            {
                return 1;
            }
        }
        place++;
    }

    /* Checking diagonal lines */
    place = 1;
    if ((spots[place] == spots[place + 4]) && (spots[place + 4] == spots[place + 8]))
    {

        if (spots[place] != ' ' && spots[place + 4] != ' ' && spots[place + 8] != ' ')
        {
            return 1;
        }

    }

    place = 3;
    if ((spots[place] == spots[place + 2]) && (spots[place + 2] == spots[place + 4]))
    {

        if (spots[place] != ' ' && spots[place + 2] != ' ' && spots[place + 4] != ' ')
        {
            return 1;
        }

    }

    return 0;

}





/*
* Function      :   seriesWinner()
* Description   :   Checks the winner of the series.
* Return Values :   Returns 1 if the score of player 1 is greater than player 2,
*                   returns 2 if the score of player 2 is greater than player 1 otherwise
*                   returns 3 if the score of player 1 and player 2 is equal.
*/

int seriesWinner(int p1Score, int p2Score)
{

    if (p1Score > p2Score)
    {
        return 1;
    }
    else if (p1Score < p2Score)
    {
        return 2;
    }
    else
    {
        return 3;
    }


}








/*
* Function      :   checkInvalidRange()
* Description   :   Checks if a number lies in the given range.
* Return Values :   Returns 1 if the number does not lie in the specified range otherwise
*                   returns 0.
*/

int checkInvalidRange(int number, int lowerLimit, int upperLimit)
{
    if (number > upperLimit || number < lowerLimit)
    {
        printf("Please enter a number in the range 1 to 9!!\n");

        return 1;
    }
    else
    {
        return 0;
    }
}






/*
* Function      :   preventOverwriting()
* Description   :   Checks if the user is trying to mark a position that is already marked.
* Return Values :   Returns 1 if the the user is trying to overwrite the position otherwise
*                   returns 0.
*/

int preventOverwriting(int inputNumber, char place[])
{
    if (place[inputNumber] != ' ')
    {
        printf("Mark already placed at this position. Please enter another position!!\n");
        return 1;
    }
    else
    {
        return 0;
    }
}






/*
* Function      :   getNum()
* Description   :   Gets an integer from user.
* Return Values :   Returns -1 if the user did not enter an integer otherwise
*                   returns the integer itself.
*/

int getNum(void)
{
    char record[121] = { 0 }; /* record stores the string */
    int number = 0;

    /* use fgets() to get a string from the keyboard */
    fgets(record, 121, stdin);

    if (sscanf(record, "%d", &number) != 1)
    {
        printf("Please enter a valid integer!!\n");
        number = -1;
    }
    return number;
}







/*
* Function      :   clearNewLine()
* Description   :   Used to clear the new line character in the string initialized using fgets().
* Return Values :   None
*/

void clearNewLine(char string[])
{
    char* newLine = strchr(string, '\n');
    if (newLine != NULL)
    {
        *newLine = '\0';
    }

}