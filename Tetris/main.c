#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define SCREEN_WIDTH 22
#define SCREEN_HEIGHT 22

int grid[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};

typedef enum {
    I,
    O,
    T,
    L,
    J,
    S,
    Z
} PieceType;

typedef enum {
    BLACK = 0,
    CYAN,
    YELLOW,
    PURPLE,
    ORANGE,
    BLUE,
    GREEN,
    RED
} PieceColor;

typedef struct {
    PieceType type;
    PieceColor color;
    int rotation;
    int x;
    int y;
    int shape[4][4];
} Piece;

Piece generatePiece() {
    Piece piece;
    piece.rotation = 0;
    piece.x = SCREEN_WIDTH / 2 - 2;
    piece.y = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece.shape[i][j] = 0;
        }
    }

    int pieceType = rand() % 7;
    switch (pieceType) {
        case I:
            piece.type = I;
            piece.color = CYAN;
            piece.shape[1][0] = 1;
            piece.shape[1][1] = 1;
            piece.shape[1][2] = 1;
            piece.shape[1][3] = 1;
            break;
        case O:
            piece.type = O;
            piece.color = YELLOW;
            piece.shape[0][0] = 1;
            piece.shape[0][1] = 1;
            piece.shape[1][0] = 1;
            piece.shape[1][1] = 1;
            break;
        case T:
            piece.type = T;
            piece.color = PURPLE;
            piece.shape[0][1] = 1;
            piece.shape[1][0] = 1;
            piece.shape[1][1] = 1;
            piece.shape[1][2] = 1;
            break;
        case L:
            piece.type = L;
            piece.color = ORANGE;
            piece.shape[0][2] = 1;
            piece.shape[1][0] = 1;
            piece.shape[1][1] = 1;
            piece.shape[1][2] = 1;
            break;
        case J:
            piece.type = J;
            piece.color = BLUE;
            piece.shape[0][0] = 1;
            piece.shape[1][0] = 1;
            piece.shape[1][1] = 1;
            piece.shape[1][2] = 1;
            break;
        case S:
            piece.type = S;
            piece.color = GREEN;
            piece.shape[0][1] = 1;
            piece.shape[0][2] = 1;
            piece.shape[1][0] = 1;
            piece.shape[1][1] = 1;
            break;
        case Z:
            piece.type = Z;
            piece.color = RED;
            piece.shape[0][0] = 1;
            piece.shape[0][1] = 1;
            piece.shape[1][1] = 1;
            piece.shape[1][2] = 1;
            break;
    }
    return piece;
}

void rotatePiece(Piece *piece) {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = piece->shape[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece->shape[i][j] = temp[i][j];
        }
    }
}

bool canMove(const Piece *piece, int newX, int newY) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece->shape[i][j] != 0) {
                int gridX = newX + j;
                int gridY = newY + i;

                if (gridX < 0 || gridX >= SCREEN_WIDTH || gridY < 0 || gridY >= SCREEN_HEIGHT) {
                    return false;
                }

                if (grid[gridY][gridX] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void mergePiece(const Piece *piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece->shape[i][j] != 0) {
                grid[piece->y + i][piece->x + j] = piece->color;
            }
        }
    }
}

void clearLines() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        bool lineFilled = true;
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            if (grid[i][j] == 0) {
                lineFilled = false;
                break;
            }
        }
        if (lineFilled) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < SCREEN_WIDTH; j++) {
                    grid[k][j] = grid[k-1][j];
                }
            }
            for (int j = 0; j < SCREEN_WIDTH; j++) {
                grid[0][j] = 0;
            }
            i--;
        }
    }
}

void printGrid() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            int cell = grid[i][j];
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, cell);
#endif
            printf("%c", cell == 0 ? ' ' : '#');
        }
        printf("\n");
    }
}

void delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

int main() {
    srand(time(0));
    Piece currentPiece = generatePiece();
    int dropInterval = 500;

    while (1) {
        if (canMove(&currentPiece, currentPiece.x, currentPiece.y + 1)) {
            currentPiece.y++;
        } else {
            mergePiece(&currentPiece);
            clearLines();
            currentPiece = generatePiece();
            if (!canMove(&currentPiece, currentPiece.x, currentPiece.y)) {
                printf("Game Over!\n");
                break;
            }
        }

        printGrid();
        delay(dropInterval);
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    return 0;
}