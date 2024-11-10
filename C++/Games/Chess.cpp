#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int BOARD_SIZE = 8;

class Piece {
public:
    char symbol;
    bool isWhite;

    Piece(char s, bool color) : symbol(s), isWhite(color) {}
    virtual ~Piece() {}
    virtual bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) = 0;
};

class Pawn : public Piece {
public:
    Pawn(bool color) : Piece(color ? 'P' : 'p', color) {}

    bool isValidMove(int startX, int startY, int endX, int endY, const vector<vector<Piece*>>& board) override {
        int direction = isWhite ? -1 : 1;
        if (endX == startX && endY == startY + direction && board[endY][endX] == nullptr) {
            return true; // Move forward
        }
        if (endX == startX && endY == startY + 2 * direction && (startY == (isWhite ? 6 : 1)) && board[endY][endX] == nullptr) {
            return true; // Double move
        }
        if (abs(endX - startX) == 1 && endY == startY + direction && board[endY][endX] != nullptr && board[endY][endX]->isWhite != isWhite) {
            return true; // Capture
        }
        return false;
    }
};

// Other pieces (Rook, Knight, Bishop, Queen, King) can be defined similarly...

class Board {
public:
    vector<vector<Piece*>> board;

    Board() {
        board.resize(BOARD_SIZE, vector<Piece*>(BOARD_SIZE, nullptr));
        setupBoard();
    }

    ~Board() {
        for (auto& row : board) {
            for (auto& piece : row) {
                delete piece;
            }
        }
    }

    void setupBoard() {
        // Set up pawns
        for (int i = 0; i < BOARD_SIZE; i++) {
            board[1][i] = new Pawn(false); // Black pawns
            board[6][i] = new Pawn(true);  // White pawns
        }
        // Set up other pieces...
    }

    void printBoard() {
        for (int y = BOARD_SIZE - 1; y >= 0; y--) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                if (board[y][x] == nullptr) {
                    cout << ". ";
                } else {
                    cout << board[y][x]->symbol << " ";
                }
            }
            cout << endl;
        }
    }

    bool movePiece(int startX, int startY, int endX, int endY) {
        if (startX < 0 || startX >= BOARD_SIZE || startY < 0 || startY >= BOARD_SIZE ||
            endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) {
            return false; // Out of bounds
        }

        Piece* piece = board[startY][startX];
        if (piece == nullptr) return false; // No piece to move

        if (piece->isValidMove(startX, startY, endX, endY, board)) {
            delete board[endY][endX]; // Capture if there's a piece
            board[endY][endX] = piece;  // Move piece
            board[startY][startX] = nullptr; // Empty the starting square
            return true;
        }
        return false;
    }
};

int main() {
    Board chessBoard;
    chessBoard.printBoard();

    // Example of moving a piece
    int startX, startY, endX, endY;
    while (true) {
        cout << "Enter move (startX startY endX endY): ";
        cin >> startX >> startY >> endX >> endY;

        if (chessBoard.movePiece(startX, startY, endX, endY)) {
            chessBoard.printBoard();
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }

    return 0;
}