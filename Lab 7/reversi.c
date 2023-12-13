//
// Author: Christopher Dometita
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include "reversi.h"

void printBoard(char [][26], int);
void legalMoveList(char [][26], int);
bool positionInBounds(int, int, int);
int moveAllDirections(char [][26], int, int, int, char, int, int);
int validMoveAllDirections(char[][26], int, int, int, char, int, int);
bool validMove(char[][26], int, int, int, char);
bool checkLegalInDirection(char [][26], int, int, int, char, int, int);
int countLegalInDirection(char [][26], int, int, int, char, int, int);
int moveCounter(char [][26], int, int, int, char, int, int);

void printBoard(char board[][26], int n) {
  char row_letter = 'a';
  char col_letter = 'a';
  printf("  ");
  for (int header = 0; header < n; header++){
    printf("%c", col_letter++);
  }
  printf("\n");
  for (int row = 0; row < n; row++) {
    printf("%c ", row_letter++);
    for (int col = 0; col < n; col++) {
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
}
void legalMoveList(char board[][26], int n) {
  int whiteCounter = 0, blackCounter = 0;
  char whiteMoveList [26][3], blackMoveList [26][3];
  // Loop for White
  printf("Available moves for W:");
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'W') {
        for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
          for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) { // When 0, = original position
              continue;
            } else {
              int counter = moveAllDirections(board, n, row, col, board[row][col], deltaRow, deltaCol);
              if (counter != 0) {
                whiteMoveList[whiteCounter][0] = deltaRow * counter + row + 'a';
                whiteMoveList[whiteCounter][1] = deltaCol * counter + col + 'a';
                whiteMoveList[whiteCounter][2] = '\0';
                whiteCounter++;
              }
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < whiteCounter - 1; i++) {
    for (int j = i + 1; j < whiteCounter; j++) {
      if (strcmp(whiteMoveList[i], whiteMoveList[j]) > 0) {
        char temp[3];
        strcpy(temp, whiteMoveList[i]);
        strcpy(whiteMoveList[i], whiteMoveList[j]);
        strcpy(whiteMoveList[j], temp);
      }
    }
  }
  for (int i = 0; i < whiteCounter; i++) {
    printf("\n%s", whiteMoveList[i]);
  }
  // Loop for Black
  printf("\nAvailable moves for B:");
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'B') {
        for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
          for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) { // When 0, = original position
              continue;
            } else {
              int counter = moveAllDirections(board, n, row, col, board[row][col], deltaRow, deltaCol);
              if (counter != 0) {
                blackMoveList[blackCounter][0] = deltaRow * counter + row + 'a';
                blackMoveList[blackCounter][1] = deltaCol * counter + col + 'a';
                blackMoveList[blackCounter][2] = '\0';
                blackCounter++;
              }
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < blackCounter - 1; i++) {
    for (int j = i + 1; j < blackCounter; j++) {
      if (strcmp(blackMoveList[i], blackMoveList[j]) > 0) {
        char temp[3];
        strcpy(temp, blackMoveList[i]);
        strcpy(blackMoveList[i], blackMoveList[j]);
        strcpy(blackMoveList[j], temp);
      }
    }
  }
  for (int i = 0; i < blackCounter; i++) {
    printf("\n%s", blackMoveList[i]);
  }
}

bool positionInBounds(int n, int row, int col) {
    if (row >= 0 && row <= n && col >= 0 && col <= n) {
      return true;
    } else {
      return false;
    }
}

int moveAllDirections(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  int counter = 0;
  int moveRow = row + deltaRow;
  int moveCol = col + deltaCol;
  
  if (positionInBounds(n, moveRow, moveCol)) {
    counter = countLegalInDirection(board, n, moveRow, moveCol, colour, deltaRow, deltaCol);
  }
  return counter;
}

int validMoveAllDirections(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  int counter = 0;
  int moveRow = row + deltaRow;
  int moveCol = col + deltaCol;
  
  if (positionInBounds(n, moveRow, moveCol)) {
    counter = moveCounter(board, n, moveRow, moveCol, colour, deltaRow, deltaCol);
  }
  return counter;
}

bool validMove(char board[][26], int n, int rowLetter, int colLetter, char colour) {
  int row = rowLetter - 'a', col = colLetter - 'a';
  if (board[row][col] == 'U') {
    for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
      for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
        if (deltaRow == 0 && deltaCol == 0) { // When 0, = original position
          continue;
        } else {
          if (checkLegalInDirection(board, n, row + deltaRow, col + deltaCol, colour, deltaRow, deltaCol)) {
            int counter = validMoveAllDirections(board, n, row, col, colour, deltaRow, deltaCol);
            for (int change = 0; change < counter +1; change++) {
              board[deltaRow * change + row][deltaCol * change + col] = colour;
            }
            return true;
          } else {
            continue;
          }
        }
      }
    }
  } else {
    return false;
  }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  if (colour == 'W') {
    if (board[row][col] == 'B') {
      row += deltaRow;
      col += deltaCol;
      while (positionInBounds(n, row, col) && board[row][col] == 'B') {
        row += deltaRow;
        col += deltaCol;
      }
      if (positionInBounds(n, row, col) && board[row][col] == 'W') {
        return true;
      }
    }
  } else {
    if (board[row][col] == 'W') {
      row += deltaRow;
      col += deltaCol;
      while (positionInBounds(n, row, col) && board[row][col] == 'W') {
        row += deltaRow;
        col += deltaCol;
      }
      if (positionInBounds(n, row, col) && board[row][col] == 'B') {
        return true;
      }
    }
  }
  return false;
}

int moveCounter(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  int counter = 1;
  if (colour == 'W') {
    if (board[row][col] == 'B') {
      counter++;
      row += deltaRow;
      col += deltaCol;
      while (positionInBounds(n, row, col) && board[row][col] == 'B') {
        counter++;
        row += deltaRow;
        col += deltaCol;
      }
      if (positionInBounds(n, row, col) && board[row][col] == 'W') {
        return counter;
      }
    }
  } else {
    if (board[row][col] == 'W') {
      counter++;
      row += deltaRow;
      col += deltaCol;
      while (positionInBounds(n, row, col) && board[row][col] == 'W') {
        counter++;
        row += deltaRow;
        col += deltaCol;
      }
      if (positionInBounds(n, row, col) && board[row][col] == 'B') {
        return counter;
      }
    }
  }
  return 0;
}

int countLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  int counter = 1;
  if (colour == 'W') {
    if (board[row][col] == 'B') {
      counter++;
      row += deltaRow;
      col += deltaCol;
      while (positionInBounds(n, row, col) && board[row][col] == 'B') {
        counter++;
        row += deltaRow;
        col += deltaCol;
      }
      if (positionInBounds(n, row, col) && board[row][col] == 'U') {
        return counter;
      }
    }
  } else {
    if (board[row][col] == 'W') {
      counter++;
      row += deltaRow;
      col += deltaCol;
      while (positionInBounds(n, row, col) && board[row][col] == 'W') {
        counter++;
        row += deltaRow;
        col += deltaCol;
      }
      if (positionInBounds(n, row, col) && board[row][col] == 'U') {
        return counter;
      }
    }
  }
  return 0;
}

int main(void) {
  // Get board dimension from user
  int dimension;
  printf("Enter the board dimension: ");
  scanf("%d", &dimension);

  // Initialize board, fill everything with 'U'
  char board[26][26];
  for (int row = 0; row < dimension; row++) {
    for (int col = 0; col < dimension; col++) {
      board[row][col] = 'U';
    }
  }
  // Initialize center black and white pieces
  int center = dimension/2;
  board[center][center] = 'W';
  board[center][center-1] = 'B';
  board[center-1][center] = 'B';
  board[center-1][center-1] = 'W';
  printBoard(board, dimension);

  // Get board configuration and plot until input = '!!!'
  char str[3] = {0}, colour, row, col;
  printf("Enter board configuration:\n");
  while (str[0] != '!' && str[1] != '!' && str[2] != '!') {
    scanf("%s", str);
    colour = str[0];
    row = str[1];
    col = str[2];
    board[row - 'a'][col - 'a'] = colour;
  }
  printBoard(board, dimension);
  
  legalMoveList(board, dimension);
  
  printf("\nEnter a move:");
  scanf("%s", str);
  colour = str[0];
  row = str[1];
  col = str[2];
  if (validMove(board, dimension, row, col, colour)) {
    printf("\nValid move.\n");
  } else {
    printf("\nInvalid move.\n");
  }

  printBoard(board, dimension);
  

  return 0;
}