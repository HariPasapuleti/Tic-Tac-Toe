#include <iostream>
#include <string>
using namespace std;

// Function to check if there's a winner
char checkWinner(char board[3][3]) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }
    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    return ' ';
}

// Function for the AI to make a move
void makeAIMove(char board[3][3], char ai, char player) {
    // Check for winning move
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == ' ') {
                board[r][c] = ai; // Try the move
                if (checkWinner(board) == ai) return; // Winning move
                board[r][c] = ' '; // Undo the move
            }
        }
    }

    // Check for blocking move
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == ' ') {
                board[r][c] = player; // Try the move
                if (checkWinner(board) == player) {
                    board[r][c] = ai; // Block opponent
                    return;
                }
                board[r][c] = ' '; // Undo the move
            }
        }
    }

    // Otherwise, pick the first empty spot
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[r][c] == ' ') {
                board[r][c] = ai;
                return;
            }
        }
    }
}

int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    const char playerX = 'X';
    const char playerO = 'O';
    char currentPlayer = playerX;
    char winner = ' ';
    int mode;
    cout << "1 - For single player mode /n 2 - Multi player mode: ";
    cin >> mode;
    bool isSinglePlayer = mode==1?true:false; // Set to true for single-player mode

    for (int i = 0; i < 9; i++) {
        // Print the game board
        cout << "   |   |   " << endl;
        cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
        cout << "___|___|___" << endl;
        cout << "   |   |   " << endl;
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
        cout << "___|___|___" << endl;
        cout << "   |   |   " << endl;
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
        cout << "   |   |   " << endl;

        // Check for a winner
        winner = checkWinner(board);
        if (winner != ' ') break;

        // Get player input or AI move
        if (isSinglePlayer && currentPlayer == playerO) {
            cout << "AI is playing" << endl;
            makeAIMove(board, playerO, playerX); // AI plays
        } else {
            int r = -1, c = -1;
            while (true) {
                cout << "Player " << currentPlayer << ", enter your move (row and column 0-2): ";
                cin >> r >> c;
                if (r < 0 || r > 2 || c < 0 || c > 2) {
                    cout << "Invalid input. Try again." << endl;
                } else if (board[r][c] != ' ') {
                    cout << "Tile is full. Try again." << endl;
                } else {
                    break;
                }
            }
            board[r][c] = currentPlayer;
        }

        // Switch players
        currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
    }

    // Print the final result
    if (winner != ' ') {
        cout << "Player " << winner << " wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}
