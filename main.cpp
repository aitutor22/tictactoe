#include <iostream>
#include <cmath>

const char PLAYER_ONE_MARKER = 'X';
const char PLAYER_TWO_MARKER = 'O';
const char UNFILLED_MARKER = ' ';

char board[3][3];
const int MAX_TURNS = sizeof(board);

void drawBoard();
void placeMarker(bool isPlayerOne, int row, int col);
bool checkValidInput(int row, int col);
bool checkWon(int row, int col);

int  main()
{
    int row, col;
    bool isPlayerOneTurn = true;
    int turn = 0;
    bool isGameRunning = true;
    bool isValidInput;

    // fills board with unfilled_marker
    std::fill(&board[0][0], &board[0][0] + sizeof(board) / sizeof(board[0][0]), ' ');

    while (isGameRunning)
    {
        // loops until we get a valid set of input from player
        isValidInput = false;
        do {
            std::cout << "Player " << (isPlayerOneTurn ? "1" : "2") << ", what is your move?\n";
            std::cin >> row >> col;

            isValidInput = !std::cin.fail() && checkValidInput(row, col);
            std::cin.clear();
            std::cin.ignore(10, '\n');

        } while (!isValidInput);
    
        placeMarker(isPlayerOneTurn, row, col);

        // after we place marker, check if player has won
        if (checkWon(row, col)) {
            std::cout << "Player " << (isPlayerOneTurn ? "1" : "2") << " has won!\n";
            isGameRunning = false;
        }
        else if (++turn >= MAX_TURNS) {
            std::cout << "It's a draw\n";
            isGameRunning = false;
        }
        drawBoard();

        // switches to other player's turn
        isPlayerOneTurn = !isPlayerOneTurn;
    }
    
    return 0;
}

void drawBoard()
{
    int rows = sizeof(board) / sizeof(board[0]);
    for (int i = 0; i < rows; ++i)
    {
        std::cout << board[i][0] << "  |  " << board[i][1] <<
            "  |  " << board[i][2] << std::endl;
        
        // draws line between rows
        if (i < rows - 1)
        {
            std::cout << "---------------\n";
        }
    }

}

bool checkValidInput(int row, int col)
{
    if (row < 0 || col < 0 || row > 2 || col > 2) return false;

    // checks if position supplied is already marked
    return board[row][col] == UNFILLED_MARKER;
}

void placeMarker(bool isPlayerOne, int row, int col)
{
    char marker = isPlayerOne ? PLAYER_ONE_MARKER : PLAYER_TWO_MARKER;
    board[row][col] = marker;
}

// given the move played, check if user has won
bool checkWon(int row, int col)
{
    // first check for horizontal/vertical victory cases
    if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) return true;
    if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) return true;

    // for top-left to bottom-right diagonals, row and col must be the same
    // for instance (0, 0) - (1, 1) - (2, 2)
    // for bottom left to top-right, one of th terms must be (0, 2) or (2, 0)
    // hence we can just use abs(row - col) == 2 to test
    if (row == col || std::abs(row - col) == 2) {
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]
            && board[1][1] != UNFILLED_MARKER) return true;
        if (board[2][0] == board[1][1] && board[1][1] == board[0][2]
            && board[1][1] != UNFILLED_MARKER) return true;
    }

    return false;
}