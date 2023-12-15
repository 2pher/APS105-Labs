/**
* @file reversi.c
* @author Christopher Dometita
* @brief This file is used for APS105 Lab 8. 2023W version
* @date 2023-03-14
*
*/
// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
//#include "reversi.h"
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printBoard(char [][26], int);
void computerMoves(char [][26], int, char);
void playGame(char [][26], int, char, char);
bool countScore(char [][26], int, char, char);
int legalMoveList(char[][26], int, char, char);
bool positionInBounds(int, int, int);
int moveAllDirections(char [][26], int, int, int, char, int, int);
int validMoveAllDirections(char[][26], int, int, int, char, int, int);
bool validMove(char[][26], int, int, int, char);
bool checkLegalInDirection(char [][26], int, int, int, char, int, int);
int makeMove(char[26][26], int, char, int*, int*);
int moveCounter(char [][26], int, int, int, char, int, int);
int countLegalInDirection(char [][26], int, int, int, char, int, int);

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

void computerMoves(char board[][26], int n, char computer) {
  int maxScore = 0, totalScore = 0, moveRow, moveCol;
  char compMove[3];
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U') {
        for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
          for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) { // When 0, it is at original position (no movement)
              continue;
            } else {
              if (checkLegalInDirection(board, n, row + deltaRow, col + deltaCol, computer, deltaRow, deltaCol)) {
                int counter = (validMoveAllDirections(board, n, row, col, computer, deltaRow, deltaCol));
                totalScore += counter; // Calculates total achievable score at specific position
                if (totalScore > maxScore) {
                  maxScore = totalScore;
                  compMove[0] = row + 'a';
                  compMove[1] = col + 'a';
                  compMove[2] = '\0';
                  moveRow = row;
                  moveCol = col;
                }
              }
            }
          }
        }
      }
      totalScore = 0; // Reinitialize the totalScore to 0 for the next grid position
    }
  }
  printf("Computer places %c at %c%c.\n", computer, compMove[0], compMove[1]);
  if (makeMove(board, n, computer, &moveRow, &moveCol) == 1) {
    printBoard(board, n);
  }
}

void playGame(char board[][26], int n, char computer, char player) {
  char playerMove[2];
  int valid = legalMoveList(board, n, computer, player);
  int winner = 1, turn = 1; // IMPLEMENT TURN, MAKE NESTED WHILE LOOP, TWO WHILE LOOPS INSIDE WHILE, SECOND WHILE FOR COMPUTER
  while (valid != 0) {
    if (valid == 3 && turn == 1) {
      printf("Enter move for colour %c (RowCol): ", player);
      scanf("%s", playerMove);
      int row = playerMove[0] - 'a';
      int col = playerMove[1] - 'a';
      int  moveRow = row;
      int moveCol = col;
      if (makeMove(board, n, player, &moveRow, &moveCol) == 1) {
        turn = 0;
        printBoard(board, n);
        valid = legalMoveList(board, n, computer, player);
        continue;
      } else {
        winner = 0;
        break; // MOVE IS INVALID. COMPUTER AUTOMATICALLY WINS.
      }
    } else if (valid == 2 && turn == 0) {
      printf("%c player has no valid move.", player);
      valid = legalMoveList(board, n, computer, player);
      continue;
    } else if (valid == 1 && turn == 0) {
      turn = 1;
      printf("%c player has no valid move.\n", computer);
      continue;
    } else if (valid == 1 && turn == 1) {
      printf("Enter move for colour %c (RowCol): ", player);
      scanf("%s", playerMove);
      int row = playerMove[0] - 'a';
      int col = playerMove[1] - 'a';
      int moveRow = row;
      int moveCol = col;
      if (makeMove(board, n, player, &moveRow, &moveCol) == 1) {
        turn = 0;
        printBoard(board, n);
        valid = legalMoveList(board, n, computer, player);
        continue;
      } else {
        winner = 0;
        break; // MOVE IS INVALID. COMPUTER AUTOMATICALLY WINS.
      }
    } else if (turn == 0) {
      turn = 1;
      computerMoves(board, n, computer);
      valid = legalMoveList(board, n, computer, player);
      continue;
    }
  }
  
  if (winner == 0) {
    printf("Invalid move.\n%c player wins.", computer);
  } else {
    if (countScore(board, n, computer, player)) {
      printf("%c player wins.", computer);
    } else {
      printf("%c player wins.", player);
    }
  }
}

bool countScore(char board[][26], int n, char computer, char player) {
  int playerCounter = 0, computerCounter = 0;
  for (int row = 0; row  < n; row++) {
    for (int col = 0; col < n; col ++) {
      if (board[row][col] == computer) {
        computerCounter++;
      } else if (board[row][col] == player) {
        playerCounter++;
      } else {
        continue;
      }
    }
  }
  if (computerCounter > playerCounter) {
    return true;
  }
  return false;
}

int legalMoveList(char board[][26], int n, char computer, char player) {
  int computerCounter = 0, playerCounter = 0, counter = 0;
  // Loop for White
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == computer) {
        for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
          for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) { // When 0, = original position
              continue;
            } else {
              if (board[row][col] == computer) {
                counter = moveAllDirections(board, n, row, col, computer, deltaRow, deltaCol);
                computerCounter += counter;
              } else {
                continue;
              }
            }
          }
        }    
      } else if (board[row][col] == player) {
        for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
          for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) { // When 0, = original position
              continue;
            } else {
              if (board[row][col] == player) {
                counter = moveAllDirections(board, n, row, col, player, deltaRow, deltaCol);
                playerCounter += counter;
              } else {
                continue;
              }
            }
          }
        }
      }    
    }
  }
  if (computerCounter > 0 && playerCounter > 0) { // BOTH PLAYERS HAVE MOVES
    return 3;
  } else if (computerCounter > 0) { // ONLY COMPUTER HAS MOVES
    return 2;
  } else if (playerCounter > 0) { // ONLY PLAYER HAS MOVES
    return 1; 
  } else { // BOTH PLAYERS HAVE NO MOVES
    return 0;
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

bool checkLegalInDirection(char board[][26], int n, int row, int col,
char colour, int deltaRow, int deltaCol) {
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

int makeMove(char board[26][26], int n, char turn, int *row, int *col) {
  bool valid = false;
  if (board[*row][*col] == 'U') {
    for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
      for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
        if (deltaRow == 0 && deltaCol == 0) { // When 0, = original position
          continue;
        } else {
          if (checkLegalInDirection(board, n, *row + deltaRow, *col + deltaCol, turn, deltaRow, deltaCol)) {
            int counter = validMoveAllDirections(board, n, *row, *col, turn, deltaRow, deltaCol);
            valid = true;
            for (int change = 0; change < counter; change++) {
              board[deltaRow * change + *row][deltaCol * change + *col] = turn;
            }
          } else {
            continue;
          }
        }
      }
    }
  }   
  if (valid) {
    return 1;
  } else {
    return 0;
  }
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

//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE
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
  
  char firstMove[2], player[2];
  printf("Computer plays (B/W): ");
  scanf("%s", firstMove);
  printBoard(board, dimension);

  if (firstMove[0] == 'B') {
    computerMoves(board, dimension, firstMove[0]);
    player[0] = 'W';
  } else {
    player[0] = 'B';
  }

  playGame(board, dimension, firstMove[0], player[0]);
  return 0;
}
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************