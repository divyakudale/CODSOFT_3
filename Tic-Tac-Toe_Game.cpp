#include <iostream>
#include <vector>

// Function prototypes
void initializeBoard(std::vector<std::vector<char>>& board);
void displayBoard(const std::vector<std::vector<char>>& board);
bool makeMove(std::vector<std::vector<char>>& board, char currentPlayer, int row, int col);
bool checkForWin(const std::vector<std::vector<char>>& board, char currentPlayer);
bool checkForDraw(const std::vector<std::vector<char>>& board);
bool playAgain();

int main() {
    char currentPlayer = 'X';
    bool gameWon, gameDraw, continueGame;

    do {
        std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));

        initializeBoard(board);
        gameWon = false;
        gameDraw = false;

        do {
            displayBoard(board);

            int row, col;
            std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            std::cin >> row >> col;

            if (makeMove(board, currentPlayer, row - 1, col - 1)) {
                gameWon = checkForWin(board, currentPlayer);
                gameDraw = checkForDraw(board);

                if (!gameWon && !gameDraw) {
                    // Switch players for the next turn
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            } else {
                std::cout << "Invalid move! Try again." << std::endl;
            }

        } while (!gameWon && !gameDraw);

        displayBoard(board);

        if (gameWon) {
            std::cout << "Player " << currentPlayer << " wins!" << std::endl;
        } else {
            std::cout << "It's a draw!" << std::endl;
        }

        continueGame = playAgain();

    } while (continueGame);

    std::cout << "Thanks for playing Tic-Tac-Toe! Goodbye." << std::endl;

    return 0;
}

void initializeBoard(std::vector<std::vector<char>>& board) {
    // Initialize the game board with empty spaces
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(const std::vector<std::vector<char>>& board) {
    // Display the current state of the board
    std::cout << "  1 2 3" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j];
            if (j < 2) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
        if (i < 2) {
            std::cout << "  -----" << std::endl;
        }
    }
    std::cout << std::endl;
}

bool makeMove(std::vector<std::vector<char>>& board, char currentPlayer, int row, int col) {
    // Check if the chosen cell is empty and make the move
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = currentPlayer;
        return true;
    }
    return false;
}

bool checkForWin(const std::vector<std::vector<char>>& board, char currentPlayer) {
    // Check for a win in rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }
    return false;
}

bool checkForDraw(const std::vector<std::vector<char>>& board) {
    // Check for a draw by examining all cells
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false; // There is an empty cell, the game is not a draw yet
            }
        }
    }
    return true; // All cells are filled, the game is a draw
}

bool playAgain() {
    // Ask the players if they want to play again
    char choice;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> choice;
    return (choice == 'y' || choice == 'Y');
}