#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<string.h>
//UwU
#include "moves.h"

int trigger = 0;
int cscr = 0;
int *scrPtr = &cscr;
char playerName[20];

typedef struct{
    char name[40];
    int score;
}Player;

void initializeGame(int board[4][4]);
void spawnTile(int board[4][4]);
void printBoard(int board[4][4]);
void printScore(int board[4][4]);
int checkGameOver(int board[4][4]);
void checkWin(int board[4][4]);

void menu();
void login();
void howToPlay();
void leaderboard();
void playGame();

int main(){
    srand(time(0));
    login();
    menu();
    return 0;
}

void login(){
    system("cls");
    printf("Welcome to 2048 Game!\nPlease enter your username (Please do not include spaces): ");
    scanf("%s", playerName);

    while(strlen(playerName)==0){
        printf("Invalid input. Enter your username again: ");
        scanf("%s", playerName);
    }
}

void menu(){
    while(1){
        system("cls");
        printf("=========== 2048 Game Menu ===========\n");
        printf("1. How to Play\n");
        printf("2. Play Game\n");
        printf("3. View Leaderboard\n");
        printf("4. Exit\n");
        printf("======================================\n");
        printf("Enter your choice (1-4): ");

        char input = _getch();
        switch(input){
            case '1': howToPlay(); break;
            case '2': system("cls"); playGame(); break;
            case '3': leaderboard(); break;
            case '4': printf("\nThank you for playing! Goodbye, %s!\n", playerName); exit(0); break;
            default: printf("\nInvalid choice! Please try again.\n"); Sleep(1000);
        }
    }
}

void howToPlay(){
    system("cls");
    printf("=========== HOW TO PLAY ===========\n\n");
    printf("2048 is an easy and fun puzzle game. It is played on a 4x4 grid using the W, A, S, D keys alternatively. Every time you press a key - all tiles slide. Tiles with the same value that bump into one-another are merged. Although there might be an optimal strategy to play, there is always some level of chance.");
    printf("\nPress any button to go back.");
    _getch();
    menu();
}

void playGame(){
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
            leaderboard();
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
            system("cls");
            printf("Game Over! Better luck next time!");
            Sleep(5000);
            leaderboard();
            break;
        }

        checkWin(board);
        system("cls");
    }
}

void leaderboard() {
    system("cls");

    Player *arr = NULL;
    int size = 0;

    // Check if players.txt exists
    FILE *pF = fopen("players.txt", "r");
    if (pF == NULL) {
        // Create the file if it doesn't exist
        pF = fopen("players.txt", "w");
        if (pF == NULL) {
            printf("Error: Could not create players.txt.\n");
            return;
        }
        fclose(pF);
        pF = fopen("players.txt", "r");
    }

    // Read players from players.txt
    char name[40];
    int flag = 0;
    while (fscanf(pF, "%s", name) != EOF) {
        if (strcmp(name, playerName) == 0) {
            flag = 1; // Mark the player as found
        }

        // Allocate memory for a new player
        arr = (Player *)realloc(arr, (size + 1) * sizeof(Player));
        if (arr == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(pF);
            return;
        }

        strcpy(arr[size].name, name);

        // Build the score file name
        char fileName[100];
        snprintf(fileName, sizeof(fileName), "Scores\\%s.txt", name);

        // Read the player's score from their score file
        FILE *file = fopen(fileName, "r");
        if (file) {
            fscanf(file, "%d", &arr[size].score);
            fclose(file);
        } else {
            arr[size].score = 0; // Default score if the file doesn't exist
        }

        size++;
    }
    fclose(pF);

    // Add the current player to players.txt if not found
    if (flag == 0) {
        pF = fopen("players.txt", "a");
        if (pF == NULL) {
            printf("Error: Could not open players.txt for appending.\n");
            free(arr);
            return;
        }

        fprintf(pF, "%s\n", playerName);
        fclose(pF);

        // Add the player to the array
        arr = (Player *)realloc(arr, (size + 1) * sizeof(Player));
        if (arr == NULL) {
            printf("Error: Memory reallocation failed.\n");
            return;
        }

        strcpy(arr[size].name, playerName);
        arr[size].score = 0; // Default score for new players
        size++;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].score < arr[j + 1].score) { 
                Player temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Display the leaderboard
    printf("=========== Leaderboard ===========\n");
    for (int i = 0; i < size; i++) {
        printf("%-20s %d\n", arr[i].name, arr[i].score);
    }
    printf("===================================\n");

    // Free allocated memory
    free(arr);

    printf("Press any key to return to the menu.\n");
    _getch();
    cscr = 0;
    menu();
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
    int flag=0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(board[i][j]==0){
                flag=1;
                break;
            }else{
                continue;
            }
        }
        if(flag){
            break;
        }
    }
    if(flag){
        do{
        x = rand()%4;
        y = rand()%4;
    } while(board[x][y] != 0);
    }
    

    int arr[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 4};  //Array that spawns 2 with 90% chance and 4 with 10% chance
    board[x][y] = arr[rand()%10];
}

void printBoard(int board[4][4]){
    printf("\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(board[i][j] == 0){
                printf(".   ");
            } 
            else{
                printf("%-4d", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printScore(int board[4][4]){
    char fileName[20];
    strcpy(fileName, "Scores\\");
    strcat(fileName, playerName);
    strcat(fileName, ".txt");
    
    //Retrieve high score from file.
    FILE *pF = fopen(fileName, "r");
    int scr=0;

    fscanf(pF, "%d", &scr);
    fclose(pF);

    //Write onto file.
    if(cscr > scr){
        scr = cscr;
        FILE *pF = fopen(fileName, "w");
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
                    leaderboard();
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
