#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define NUM_SHIPS 3

char playerBoard[SIZE][SIZE];
char computerBoard[SIZE][SIZE];

void initializeBoards() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            playerBoard[i][j] = '-';
            computerBoard[i][j] = '-';
        }
    }
}



void printBoard(char board[SIZE][SIZE], int hideShips) {
    printf("  ");
    for (int i = 0; i < SIZE; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            if (hideShips && board[i][j] == 'S')
                printf("- ");
            else
                printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}



void placePlayerShipsManually() {
    int shipsPlaced = 0;
    int row, col;

    printf("\nPlace your ships manually (Total: %d):\n", NUM_SHIPS);
    while (shipsPlaced < NUM_SHIPS) {
        printf("Enter coordinates for ship %d (row col): ", shipsPlaced + 1);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }

        if (playerBoard[row][col] == 'S') {
            printf("You already placed a ship here. Choose another spot.\n");
            continue;
        }

        playerBoard[row][col] = 'S';
        shipsPlaced++;
    }
}



void placeShipsRandomly(char board[SIZE][SIZE]) {
    int shipsPlaced = 0;
    while (shipsPlaced < NUM_SHIPS) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (board[row][col] != 'S') {
            board[row][col] = 'S';
            shipsPlaced++;
        }
    }
}




int playerTurn() {
    int row, col;

    printf("\nYour turn! Enter coordinates to fire (row col): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        printf("Invalid coordinates. Try again.\n");
        return 0;
    }

    if (computerBoard[row][col] == 'S') {
        printf("Hit!\n");
        computerBoard[row][col] = 'X';
        return 1;
    } else if (computerBoard[row][col] == '-') {
        printf("Miss.\n");
        computerBoard[row][col] = 'O';
        return 0;
    } else {
        printf("Already targeted. Try different coordinates.\n");
        return 0;
    }
}

int computerTurn() {
    int row = rand() % SIZE;
    int col = rand() % SIZE;

    printf("\nComputer fires at (%d, %d): ", row, col);

    if (playerBoard[row][col] == 'S') {
        printf("Hit!\n");
        playerBoard[row][col] = 'X';
        return 1;
    } else if (playerBoard[row][col] == '-') {
        printf("Miss.\n");
        playerBoard[row][col] = 'O';
        return 0;
    } else {
        // Already targeted, try again
        return computerTurn();
    }
}

int checkWin(char board[SIZE][SIZE]) {
    int shipCount = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == 'S')
                shipCount++;
    return shipCount == 0;
}

int main() {
    srand(time(NULL));
    initializeBoards();

    // User Manual
    printf("=== Welcome to Battleship (5x5) ===\n\n");
    printf("Rules:\n");
    printf("1. The game board is 5x5.\n");
    printf("2. Each player (you and the computer) has %d ships.\n", NUM_SHIPS);
    printf("3. Ships are placed on the board as 'S'.\n");
    printf("4. You will place your ships manually by entering coordinates.\n");
    printf("5. The computer will place its ships randomly.\n");
    printf("6. During your turn, choose coordinates to fire at.\n");
    printf("7. A 'Hit' will mark the ship with 'X', and a 'Miss' with 'O'.\n");
    printf("8. First to sink all opponent's ships wins the game!\n");
    printf("\nPress ENTER to start the game...");

    getchar(); // Consume any leftover newline from previous input
    getchar(); // Wait for user to press ENTER

    placePlayerShipsManually(); // Player places ships
    placeShipsRandomly(computerBoard); // Computer places ships

    while (1) {
        printf("\nYour Board:\n");
        printBoard(playerBoard, 0);

        printf("\nComputer's Board:\n");
        printBoard(computerBoard, 1);

        if (playerTurn()) {
            if (checkWin(computerBoard)) {
                printf("\nComputer's Board:\n");
                printBoard(computerBoard, 0);
                printf("\nYou sunk all enemy ships! You win!\n");
                break;
            }
        }

        if (computerTurn()) {
            if (checkWin(playerBoard)) {
                printf("\nYour Board:\n");
                printBoard(playerBoard, 0);
                printf("\nThe computer sunk all your ships! You lose.\n");
                break;
            }
        }
    }

    return 0;
}