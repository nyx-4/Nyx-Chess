#include <iostream>
#include <fstream>
using namespace std;

class Chess {
private:
    char ChessArr[8][8];

public:
    // Chess();
    // ~Chess();

    void Test() {
        string FilePath = "chess.txt";
        // LoadGameFromFile(FilePath);
        // ShowGame(ChessArr);
        // cout << "\nNew Game Init\n";
        // InitNewGame();
        // ShowGame(ChessArr);
        FilePath = "chess.txt";
        // SaveGameToFile(FilePath);
        LoadGameFromFile(FilePath);
        ShowGame(ChessArr);
    }

    void LoadGameFromFile(string FilePath) {
        fstream GameFile;
        GameFile.open(FilePath);
        int i = 0;
        while (!GameFile.eof()) {
            char ch;
            ch = char(GameFile.get());
            if (ch != '\n') {
                ChessArr[i / 8][i % 8] = ch;
                i += 1;
            }
        }
        GameFile.close();
    }

    void SaveGameToFile(string FilePath) {
        fstream GameFile;
        // GameFile.open(FilePath, ios::ate);
        // GameFile.close();
        GameFile.open(FilePath, ios_base::app);
        char ch;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                ch = ChessArr[i][j];
                GameFile << ch;
            }
            ch = '\n';
            GameFile << ch;
        }
        GameFile.close();
    }

    void InitNewGame() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (i == 0) {
                    if (j == 0 || j == 7) ChessArr[i][j] = 'R';
                    else if (j == 1 || j == 6) ChessArr[i][j] = 'N';
                    else if (j == 2 || j == 5) ChessArr[i][j] = 'B';
                    else if (j == 3) ChessArr[i][j] = 'Q';
                    else if (j == 4) ChessArr[i][j] = 'K';
                }
                else if (i == 7) {
                    if (j == 0 || j == 7) ChessArr[i][j] = 'r';
                    else if (j == 1 || j == 6) ChessArr[i][j] = 'n';
                    else if (j == 2 || j == 5) ChessArr[i][j] = 'b';
                    else if (j == 3) ChessArr[i][j] = 'q';
                    else if (j == 4) ChessArr[i][j] = 'k';
                }
                else if (i == 1) ChessArr[i][j] = 'P';
                else if (i == 6) ChessArr[i][j] = 'p';
                else ChessArr[i][j] = '.';
            }
        }
    }

    void MovePieceGlobally(string LongAlgebraicNotation) {
        return;
    }

    // char* MovePieceLocally(string LongAlgebraicNotation, char ChessArrLocal[8][8]) {
    //     return;
    // }

    // string* ValidMovesOfPiece(char Piece, char ChessArrLocal[8][8]) {
    //     return;
    // }

    void ShowGame(char ChessArrLocal[8][8]) {
        for (int i = 0; i < 8; i += 1) {
            for (int j = 0; j < 8; j += 1)
                cout << ChessArrLocal[i][j];
            cout << "\n";
        }
    }

    // void Multiplayer

};

int main() {
    Chess ch;
    ch.Test();
    return 0;
}
