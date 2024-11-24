#include<iostream>
#include<fstream>
using namespace std;

void ShowGame(char ChessArrLocal[8][9]) {
    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 8; j += 1)
            cout << ChessArrLocal[i][j];
        cout << "\n";
    }
}

char ToExtendedAlgerbraic(short MoveInShort) {
    int OriginalPosition = MoveInShort / 64 % 64, NewPosition = MoveInShort % 64;
    char ExtendedAlgebraic[6];
    ExtendedAlgebraic[0] = OriginalPosition / 8 + 97;
    ExtendedAlgebraic[1] = OriginalPosition % 8 + 49;
    ExtendedAlgebraic[2] = '-';
    ExtendedAlgebraic[3] = NewPosition / 8 + 97;
    ExtendedAlgebraic[4] = NewPosition % 8 + 49;
    ExtendedAlgebraic[5] = '\0';
    // char* pExtendedAlgebraic = &ExtendedAlgebraic[0];
    return ExtendedAlgebraic[0];
}

short ToShort(char MoveInExtendedAlgebraic[]) {
    return 2;
}

short* GetValidMoves(char ChessArrLocal[8][9], short FindValidMovesOfThisPiece) {
    // Make this Array As long as possible moves of that particular piece
    // Returns only non-empty Moves.
    // Moves are 16-bit short int, Four Control, Six Original Position, Six New Position.
    // Two Control Bits
        // 0000: Normal Move
        // 1000: New Position is invalid (garbage).
        // 0001: Capture Move
        // 0010: Castling (King Side)
        // 0011: Castling (Queen Side)
        // 0100: Check White
        // 0101: Promotion
        // 0110: En-Passant
        // 0111: Checkmate White
        // 1100: Check Black
        // 1111: Checkmate Black

    short ValidMoves[20];
    int curIndex_ValidMoves = -1;
    short OriginalPosition = FindValidMovesOfThisPiece / 64 % 64;
    cout << OriginalPosition;
    return NULL;
}

int main() {
    char ChessArr[8][9] = {
        "RNBQKBNR",
        "PPPPPPPP",
        "........",
        "........",
        "........",
        "........",
        "pppppppp",
        "rnbqkbnr",
    };
    // ShowGame(ChessArr);
    // GetValidMoves(ChessArr, 2496);
    char Move = ToExtendedAlgerbraic(2496);
    cout << *(&Move);
    return 0;
}
