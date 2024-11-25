#include<stdio.h>
#include "moves.h"

void moveUp(int board[4][4], int* cscr){
    for(int j = 0; j < 4; j++){  
        for(int i = 1; i < 4; i++){  
            int k = i; //Temporary variable to mimic i and be able to decrement itself.
            while(k > 0 && board[k-1][j] == 0){  
                int temp= board[k-1][j];  
                board[k-1][j] = board[k][j];
                board[k][j] = temp;
                k--;  // Move Up
            }
        }
    }
    
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 3; i++){  
            if(board[i][j] == board[i+1][j] && board[i][j] != 0){  // If tiles are the same
                board[i][j] *= 2;  // Double the value
                cscr += board[i][j];
                board[i+1][j] = 0;  
            }
        }
    }
    
    // After combining, shift all numbers to the Up again
    for(int j = 0; j < 4; j++){
        for(int i = 1; i < 4; i++){
            int k = i;
            while(k > 0 && board[k-1][j] == 0){  
                board[k-1][j] = board[k][j];
                board[k][j] = 0;
                k--;  // Move Up
            }
        }
    }
}
void moveLeft(int board[4][4], int* cscr){
    for(int i = 0; i < 4; i++){  
        for(int j = 1; j < 4; j++){  
            int k = j; //Temporary variable to mimic i and be able to decrement itself.
            while(k > 0 && board[i][k-1] == 0){  
                int temp= board[i][k-1];  
                board[i][k-1] = board[i][k];
                board[i][k] = temp;
                k--;  // Move left
            }
        }
    }
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){  
            if(board[i][j] == board[i][j+1] && board[i][j] != 0){  // If tiles are the same
                board[i][j] *= 2;  // Double the value
                cscr += board[i][j];
                board[i][j+1] = 0;  
            }
        }
    }
    
    // After combining, shift all numbers to the left again
    for(int i = 0; i < 4; i++){
        for(int j = 1; j < 4; j++){
            int k = j;
            while(k > 0 && board[i][k-1] == 0){  // While the left cell is empty
                board[i][k-1] = board[i][k];
                board[i][k] = 0;
                k--;  // Move left
            }
        }
    }
}
void moveRight(int board[4][4], int* cscr){
    for(int i = 0; i < 4; i++){  
        for(int j = 2; j >= 0; j--){  
            int k = j; //Temporary variable to mimic i and be able to decrement itself.
            while(k < 3 && board[i][k+1] == 0){  
                int temp = board[i][k+1];  
                board[i][k+1] = board[i][k];
                board[i][k] = temp;
                k++;  // Move right
            }
        }
    }
    
    for(int i = 0; i < 4; i++){
        for(int j = 3; j > 0; j--){  
            if(board[i][j] == board[i][j-1] && board[i][j] != 0){  // If tiles are the same
                board[i][j] *= 2;  // Double the value
                cscr += board[i][j];
                board[i][j-1] = 0;  
            }
        }
    }
    
    for(int i = 0; i < 4; i++){
        for(int j = 2; j >= 0; j--){
            int k = j;
            while(k < 3 && board[i][k+1] == 0){ 
                board[i][k+1] = board[i][k];
                board[i][k] = 0;
                k++;  // Move right
            }
        }
    }
}
void moveDown(int board[4][4], int* cscr){
    for(int j = 0; j < 4; j++){  
        for(int i = 2; i >=0; i--){  
            int k = i; //Temporary variable to mimic i and be able to decrement itself.
            while(k < 3 && board[k+1][j] == 0){  
                int temp= board[k+1][j];  //Swapping the cell with the empty cell below of it.
                board[k+1][j] = board[k][j];
                board[k][j] = temp;
                k++;  // Move Down
            }
        }
    }
    
    for(int j = 0; j < 4; j++){
        for(int i = 2; i >= 0; i--){  
            if(board[i][j] == board[i+1][j] && board[i][j] != 0){  // If tiles are the same
                board[i+1][j] *= 2;  // Double the value
                cscr += board[i+1][j];
                board[i][j] = 0;  
            }
        }
    }
    
    // After combining, shift all numbers to the Down again
    for(int j = 0; j < 4; j++){
        for(int i = 2; i >= 0; i--){
            int k = i;
            while(k < 3 && board[k+1][j] == 0){  
                board[k+1][j] = board[k][j];
                board[k][j] = 0;
                k++;  // Move Down
            }
        }
    }
}
