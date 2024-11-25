#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
//UwU
#include "moves.h"

int trigger = 0;
int cscr = 0;
int *scrPtr = &cscr;

void initializeGame(int board[4][4]);
void spawnTile(int board[4][4]);
void printBoard(int board[4][4]);
void printScore(int board[4][4]);
int checkGameOver(int board[4][4]);
void checkWin(int board[4][4]);

int main(){
    srand(time(0));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    int board[4][4];
    int gameOver = 0;

    initializeGame(board);
    char input;

    while(gameOver==0){
        printScore(board);
        printBoard(board);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Press W (Up), A (Left), S (Down), D (Right) to move tiles. Press Q to exit.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        input = _getch();

        if(input=='q' || input=='Q'){
            break;
        }

        switch(tolower(input)){
            case 'w': moveUp(board, scrPtr); spawnTile(board); break;
            case 'a': moveLeft(board, scrPtr); spawnTile(board); break;
            case 'd': moveRight(board, scrPtr); spawnTile(board); break;
            case 's': moveDown(board, scrPtr); spawnTile(board); break;
            case '8': moveUp(board, scrPtr); spawnTile(board); break;
            case '4': moveLeft(board, scrPtr); spawnTile(board); break;
            case '6': moveRight(board, scrPtr); spawnTile(board); break;
            case '2': moveDown(board, scrPtr); spawnTile(board); break;
            default: system("cls"); printf("Invalid Input.\n"); continue;
        }

        gameOver = checkGameOver(board);
        if(gameOver==1){
            printBoard(board);
            printf("Game Over! Better luck next time!");
            Sleep(5000);
        }

        checkWin(board);
        system("cls");
    }

    return 0;
}

void initializeGame(int board[4][4]){
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            board[i][j] = 0;
        }
    }
    spawnTile(board);
    spawnTile(board);
}

void spawnTile(int board[4][4]){
    int x, y;
    do{
        x = rand()%4;
        y = rand()%4;
    } while(board[x][y] != 0);

    int arr[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 4};  //Array that spawns 2 with 90% chance and 4 with 10% chance
    board[x][y] = arr[rand()%10];
}

void printBoard(int board[4][4]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);       // Get console dimensions

    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1; // Console width
    int boardWidth = 4 * 4 + 3;  // Each number occupies 4 spaces, with 3 spaces between columns
    int padding = (consoleWidth - boardWidth) / 2;     // Calculate horizontal padding

    printf("\n");

    for (int i = 0; i < 4; i++) {
        // Move cursor to the calculated starting position for each row
        COORD position = {padding, (SHORT)(csbi.dwCursorPosition.Y + i)};
        SetConsoleCursorPosition(hConsole, position);

        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                printf(".   ");
            } else {
                printf("%-4d", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printScore(int board[4][4]){
    
    //Retrieve high score from file.
    FILE *pF = fopen("hscr.txt", "r");
    int scr=0;

    fscanf(pF, "%d", &scr);
    fclose(pF);

    //Write onto file.
    if(cscr > scr){
        scr = cscr;
        FILE *pF = fopen("hscr.txt", "w");
        fprintf(pF, "%d", scr);
        fclose(pF);
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("CURRENT SCORE: %d\n", cscr);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("HIGH SCORE: %d\n", scr);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void checkWin(int board[4][4]){
    if(trigger==1){
        return;
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(board[i][j]==2048){
                system("cls");
                printBoard(board);
                char ch;
                printf("Congratulations! You have won. Do you want to continue? (Y/N): ");
                ch = _getch();
                if(tolower(ch)=='y'){
                    trigger = 1;
                    return;
                }
                else if(tolower(ch)=='n'){
                    printf("\nThank you for playing!");
                    Sleep(3000);
                    exit(1);
                }

            }
        }
    }
}

int checkGameOver(int board[4][4]) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                return 0;  // Game continues if there’s an empty tile
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {  // Check only until the second-last column
            if (board[i][j] == board[i][j + 1]) {
                return 0;  // Game continues if there’s a possible horizontal merge
            }
        }
    }

    
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {  // Check only until the second-last row
            if (board[i][j] == board[i + 1][j]) {
                return 0;  // Game continues if there’s a possible vertical merge
            }
        }
    }

    return 1;  // Game is over if no empty tiles or possible merges
}

