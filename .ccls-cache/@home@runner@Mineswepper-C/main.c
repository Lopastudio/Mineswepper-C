#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10
#define NUM_MINES 15

char board[BOARD_SIZE][BOARD_SIZE];   // Game board
char visible[BOARD_SIZE][BOARD_SIZE]; // Visibility status of cells

void initialize() {
  // Initialize the board with empty cells
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = ' ';
      visible[i][j] = 0; // All cells are initially hidden
    }
  }

  // Place mines randomly
  srand(time(NULL));
  for (int k = 0; k < NUM_MINES; k++) {
    int x = rand() % BOARD_SIZE;
    int y = rand() % BOARD_SIZE;
    if (board[x][y] != '*') {
      board[x][y] = '*';
      // Increment counts of neighboring cells
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          int nx = x + dx;
          int ny = y + dy;
          if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE &&
              board[nx][ny] != '*') {
            board[nx][ny]++;
          }
        }
      }
    } else {
      k--; // If a mine is already present, retry
    }
  }
}

void printBoard() {
  printf("  ");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i);
  }
  printf("\n");

  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i);
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (visible[i][j]) {
        printf("%c ", board[i][j]);
      } else {
        printf(". ");
      }
    }
    printf("\n");
  }
}

void revealCell(int x, int y) {
  if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || visible[x][y]) {
    return;
  }
  visible[x][y] = 1;
  if (board[x][y] == ' ') {
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        revealCell(x + dx, y + dy);
      }
    }
  }
}

int main() {
  initialize();

  while (1) {
    printBoard();

    int x, y;
    printf("Enter coordinates (x y): ");
    scanf("%d %d", &x, &y);

    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
      printf("Invalid coordinates!\n");
      continue;
    }

    if (board[x][y] == '*') {
      printf("Game Over! You hit a mine!\n");
      break;
    }

    revealCell(x, y);

    int allVisible = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j] != '*' && !visible[i][j]) {
          allVisible = 0;
          break;
        }
      }
      if (!allVisible) {
        break;
      }
    }

    if (allVisible) {
      printf("Congratulations! You cleared the minefield!\n");
      break;
    }
  }

  return 0;
}
