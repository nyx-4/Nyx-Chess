//
//
//                    #        TM
//     $    $  $     $ #     #
//     $$   $   $   $   #   #
//     $ $  $    $ $     # #
//     $  $ $     $       #
//     $   $$     $      # #
//     $    $     $     #   #
//
//
//          Nyx-Chess
// A project by: THE CULT OF THE LINUX
// Authors: IsmailHamza
//
// 
// - Run/Test in 9x36 zsh Terminal
// 
// All rights reserved



#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;
#include "NyxChess.h"


// A place for local functions

void _Menu() { // A dummy Menu to test variables, final values should be assigned in Menu()
    SQ_BG_BLACK = BG_BLACK;
    SQ_BG_WHITE = BG_WHITE;
    PC_WT_PAWN = "p";
    PC_WT_ROOK = "r";
    PC_WT_KNIGHT = "n";
    PC_WT_BISHOP = "b";
    PC_WT_QUEEN = "q";
    PC_WT_KING = "k";
    PC_BL_PAWN = "P";
    PC_BL_ROOK = "R";
    PC_BL_KNIGHT = "N";
    PC_BL_BISHOP = "B";
    PC_BL_QUEEN = "Q";
    PC_BL_KING = "K";
    PC_EMPTY = " ";
}


bool _isValidChInFile(char ch) {
    switch (ch) {
        case '\n':
        case '.':
        case -1:

        case 'p':
        case 'r':
        case 'n':
        case 'b':
        case 'q':
        case 'k':
            return true;

        case 'P':
        case 'R':
        case 'N':
        case 'B':
        case 'Q':
        case 'K':
            return true;
    }
    return false;
}

void _PrintPiece(char ch) {
    switch (ch) {
        default: cout << SQ_FG_WHITE << PC_EMPTY << " " << FG_DEFAULT; break;

        case 'p': cout << SQ_FG_WHITE << PC_WT_PAWN << " " << FG_DEFAULT; break;
        case 'r': cout << SQ_FG_WHITE << PC_WT_ROOK << " " << FG_DEFAULT; break;
        case 'n': cout << SQ_FG_WHITE << PC_WT_KNIGHT << " " << FG_DEFAULT; break;
        case 'b': cout << SQ_FG_WHITE << PC_WT_BISHOP << " " << FG_DEFAULT; break;
        case 'q': cout << SQ_FG_WHITE << PC_WT_QUEEN << " " << FG_DEFAULT; break;
        case 'k': cout << SQ_FG_WHITE << PC_WT_KING << " " << FG_DEFAULT; break;

        case 'P': cout << SQ_FG_BLACK << PC_BL_PAWN << " " << FG_DEFAULT; break;
        case 'R': cout << SQ_FG_BLACK << PC_BL_ROOK << " " << FG_DEFAULT; break;
        case 'N': cout << SQ_FG_BLACK << PC_BL_KNIGHT << " " << FG_DEFAULT; break;
        case 'B': cout << SQ_FG_BLACK << PC_BL_BISHOP << " " << FG_DEFAULT; break;
        case 'Q': cout << SQ_FG_BLACK << PC_BL_QUEEN << " " << FG_DEFAULT; break;
        case 'K': cout << SQ_FG_BLACK << PC_BL_KING << " " << FG_DEFAULT; break;
    }
}

void _PrintPossibleMoves(bool Arr[]) {
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++)
            cout << Arr[i * 8 + j] << " ";
        cout << endl;
    }
}

/*
                                    1
                      #        TM   2
       $    $  $     $ #     #      3
       $$   $   $   $   #   #       4
       $ $  $    $ $     # #        5
       $  $ $     $       #         6
       $   $$     $      # #        7
       $    $     $     #   #       8
                                    9
*/
void Loading(); // Animated Nyx at start



// Game: Some options like:
//      - New Game as White or Black or Random
//      - Open Previous saved game
//      - Initial Timer
//      - Incremental Timer
//
// Tweaks: In game settings like:
//      - UI tweaks like 
//          - Show Board co-ordinates
//          - Show board highlights (Last move, if false override SQ_BG_MV_PRE and SQ_BG_MV_NXT using if else)
//          - Blindfold Chess (Don't display Chess Symbols)
//          - Use Unicode pieces (Use Unicode Set1 or Unicode Set2 or ASCII Alphabets, set using switch statement)
//          - Show move list in Unicode (Show last 4 moves using Unicode)
//      - GUI interface colour scheme (Stored as \033 char, allow duplicates)
//          - Board White background colour (The background colour for white squares)
//          - Board Black background colour
//          - Piece White colour
//          - Piece Black colour
//          - Highlighted square (For Keyboard navigation)
//          - Previous move source square
//          - Previous move destinaton square
//      - Navigation Keys (For Keyboard Navigation, select square using ENTER or SPACE)
// Help: A man page for our chess program
//      - The documentation of How to use our Chess Program
// About: A page about us. Who we are (The Cult of The Linux), How to reach us and contact us, Report bugs etc stuff.
/*
  Game... Tweaks. Help... About..   1
                                    2
                                    3
                                    4
                                    5
                                    6
                                    7
                                    8
                                    9
*/
void Menu();    // An interactive menu after Loading

bool LoadGame(string FilePath) {     // Path to the Game loaded, load it in GAME_ARR Array, extension is ".xchs"
    fstream GameFile;
    GameFile.open(FilePath);
    int i = 0, P = 0, p = 0, K = 0, k = 0, r = 0, b = 0, q = 0, n = 0, R = 0, B = 0, Q = 0, N = 0;
    char ch;
    while (!GameFile.eof()) {
        ch = char(GameFile.get());
        if (!_isValidChInFile(ch)) {
            cout << FG_RED << "Invalid character in Nyx-Chess file: " << ch << RESET;
            return false;
        }
        else if (ch != '\n') {
            switch (ch) {
                case 'p': p++;break;
                case 'k': k++;break;
                case 'r': r++;break;
                case 'n': n++;break;
                case 'b': b++;break;
                case 'q': q++;break;

                case 'P': P++;break;
                case 'K': K++;break;
                case 'R': R++;break;
                case 'N': N++;break;
                case 'B': B++;break;
                case 'Q': Q++;break;
            }


            CHESS_ARR[i / 8][i % 8] = ch;
            i++;
        }
    }
    if (r > 2) p += r - 2;
    if (n > 2) p += n - 2;
    if (b > 2) p += b - 2;
    if (q > 1) p += q - 1;

    if (R > 2) P += R - 2;
    if (N > 2) P += N - 2;
    if (B > 2) P += B - 2;
    if (Q > 1) P += Q - 1;

    if (k != 1 || K != 1 || p > 8 || P > 8) {
        cout << FG_RED << "Invalid Game in Nyx-Chess file" << RESET;
        return false;
    }
    GameFile.close();
    return true;
}

void NewGame() { // Make a new game a.k.a load default game(call LoadGame with default Path)
    LoadGame("chess.txt");
}

void SaveGame(string FilePath) {     // Path to save game strored GAME_ARR, using ".xchs" extension
    fstream GameFile;
    GameFile.open(FilePath, ios_base::out);
    char ch;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ch = CHESS_ARR[i][j];
            GameFile << ch;
        }
        if (i != 7) {
            ch = '\n';
            GameFile << ch;
        }
    }
    GameFile.close();
}

void PrintGame() {   // Prints the game stored in GAME_ARR, along with any UI/GUI overlays.
    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 8; j += 1) {
            if ((i + j) % 2) cout << SQ_BG_BLACK;
            else cout << SQ_BG_WHITE;
            _PrintPiece(CHESS_ARR[i][j]);
            cout << RESET;
        }
        cout << "\n";
    }
}

long int curTime() {
    long int Time;
    time(&Time);
    return Time;
}

unsigned long TimePassed() {   // Returns curTime - TimeGameStarted
    return curTime() - TIME_GAME_STARTED;
}

int TimeRemainingWhite() {    // Returns TIME_TOTAL - TimePassed().
    return TIME_TOTAL - TimePassed() + (TIME_INCREMENT * MOVES_MADE_WHITE);
}

int TimeRemainingBlack() {    // Returns TIME_TOTAL - TimePassed() + incremented time
    return TIME_TOTAL - TimePassed() + (TIME_INCREMENT * MOVES_MADE_BLACK);
}

int GameState() {   // Returns (0, Ongoing); (1, White in Check); (2, White in Stalemate); (3, White Lost);
    //              // Returns (4, Draw);    (5, Black in Check); (6, Black in Stalemate); (7, Black Lost);
    return 0;
}

string mvShort_HR(short mv) {   // Convert short to Human Readable Long Algebraic Notation
    short  PR;
    string IR, IC, FR, FC, XS, PP, CHK = " ";

    IC = ((mv >> 13 & 0b111) + 65);
    IR = ((mv >> 10 & 0b111) + 48);
    FC = ((mv >> 7 & 0b111) + 65);
    FR = ((mv >> 4 & 0b111) + 48);
    PR = mv >> 1 & 0b111;
    XS = ((mv >> 0 & 0b1) ? "x" : "-");

    switch (PR) {
        case 0: PP = " ";break;
        case 1: PP = "R";break;
        case 2: PP = "N";break;
        case 3: PP = "B";break;
        case 4: PP = "Q";break;
        case 5: PP = " ";break;
    }
    if (GameState() % 2 == 1) CHK = "+";    // If Game State is odd
    return IC + IR + XS + FC + FR + "=" + PP + CHK;
}

short mvHR_Short(string mv) {  // Convert Human Readable Long Algebraic Notation to short
    int PR = 0;
    switch (mv[6]) {
        case '.': PR = 0; break;
        case 'R': PR = 1; break;
        case 'N': PR = 2; break;
        case 'B': PR = 3; break;
        case 'Q': PR = 4; break;
    }
    return (mv[0] - 65) * 8192 + (mv[1] - 48) * 1024 + (mv[3] - 65) * 128 + (mv[4] - 48) * 16 + PR * 2 + ((mv[2] == 'x') ? 1 : 0);
}

// short mvInput_Short(string mv) {    // Convert User Input command to short
//     while (mv.length() < 7)
//         mv += " ";
//     return mvHR_Short();
// }

bool* AllPossibleMoves(short Piece) {   // Returns a 8x8 boolean array with 1 meaning it can go there and 0 means can't.
    int Col = (Piece >> 13 & 0b111), Row = (Piece >> 10 & 0b111);
    char Pc = CHESS_ARR[Row][Col];
    static bool PossibleMoves[64];
    for (int i = 0;i < 64; i++) PossibleMoves[i] = 0;
    switch (Pc) {
        case 'r':
            for (int i = Row - 1; i >= 0; i--) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'A' && CHESS_ARR[i][Col] <= 'Z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Row + 1; i <= 7; i++) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'A' && CHESS_ARR[i][Col] <= 'Z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Col - 1; i >= 0; i--) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'A' && CHESS_ARR[Row][i] <= 'Z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            for (int i = Col + 1; i <= 7; i++) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'A' && CHESS_ARR[Row][i] <= 'Z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            break;

        case 'n':
            if (Row + 2 <= 7 && Col + 1 <= 7 && ((CHESS_ARR[Row + 2][Col + 1] >= 'A' && CHESS_ARR[Row + 2][Col + 1] <= 'Z') || CHESS_ARR[Row + 2][Col + 1] == '.'))
                PossibleMoves[(Row + 2) * 8 + Col + 1] = true;
            if (Row + 2 <= 7 && Col - 1 >= 0 && ((CHESS_ARR[Row + 2][Col - 1] >= 'A' && CHESS_ARR[Row + 2][Col - 1] <= 'Z') || CHESS_ARR[Row + 2][Col - 1] == '.'))
                PossibleMoves[(Row + 2) * 8 + Col - 1] = true;
            if (Row + 1 <= 7 && Col + 2 <= 7 && ((CHESS_ARR[Row + 1][Col + 2] >= 'A' && CHESS_ARR[Row + 1][Col + 2] <= 'Z') || CHESS_ARR[Row + 1][Col + 2] == '.'))
                PossibleMoves[(Row + 1) * 8 + Col + 2] = true;
            if (Row + 1 <= 7 && Col - 2 >= 0 && ((CHESS_ARR[Row + 1][Col - 2] >= 'A' && CHESS_ARR[Row + 1][Col - 2] <= 'Z') || CHESS_ARR[Row + 1][Col - 2] == '.'))
                PossibleMoves[(Row + 1) * 8 + Col - 2] = true;
            if (Row - 2 >= 0 && Col + 1 <= 7 && ((CHESS_ARR[Row - 2][Col + 1] >= 'A' && CHESS_ARR[Row - 2][Col + 1] <= 'Z') || CHESS_ARR[Row - 2][Col + 1] == '.'))
                PossibleMoves[(Row - 2) * 8 + Col + 1] = true;
            if (Row - 1 >= 0 && Col + 2 <= 7 && ((CHESS_ARR[Row - 1][Col + 2] >= 'A' && CHESS_ARR[Row - 1][Col + 2] <= 'Z') || CHESS_ARR[Row - 1][Col + 2] == '.'))
                PossibleMoves[(Row - 1) * 8 + Col + 2] = true;
            if (Row - 2 >= 0 && Col - 1 >= 0 && ((CHESS_ARR[Row - 2][Col - 1] >= 'A' && CHESS_ARR[Row - 2][Col - 1] <= 'Z') || CHESS_ARR[Row - 2][Col - 1] == '.'))
                PossibleMoves[(Row - 2) * 8 + Col - 1] = true;
            if (Row - 1 >= 0 && Col - 2 >= 0 && ((CHESS_ARR[Row - 1][Col - 2] >= 'A' && CHESS_ARR[Row - 1][Col - 2] <= 'Z') || CHESS_ARR[Row - 1][Col - 2] == '.'))
                PossibleMoves[(Row - 1) * 8 + Col - 2] = true;
            break;

        case 'b':
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col - i < 0) break;
                else if (CHESS_ARR[Row - i][Col - i] == '.') PossibleMoves[(Row - i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row - i][Col - i] >= 'A' && CHESS_ARR[Row - i][Col - i] <= 'Z') {
                    PossibleMoves[(Row - i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col - i < 0) break;
                else if (CHESS_ARR[Row + i][Col - i] == '.') PossibleMoves[(Row + i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row + i][Col - i] >= 'A' && CHESS_ARR[Row + i][Col - i] <= 'Z') {
                    PossibleMoves[(Row + i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col + i >7) break;
                else if (CHESS_ARR[Row - i][Col + i] == '.') PossibleMoves[(Row - i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row - i][Col + i] >= 'A' && CHESS_ARR[Row - i][Col + i] <= 'Z') {
                    PossibleMoves[(Row - i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col + i > 7) break;
                else if (CHESS_ARR[Row + i][Col + i] == '.') PossibleMoves[(Row + i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row + i][Col + i] >= 'A' && CHESS_ARR[Row + i][Col + i] <= 'Z') {
                    PossibleMoves[(Row + i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            break;

        case 'q':
            for (int i = Row - 1; i >= 0; i--) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'A' && CHESS_ARR[i][Col] <= 'Z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Row + 1; i <= 7; i++) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'A' && CHESS_ARR[i][Col] <= 'Z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Col - 1; i >= 0; i--) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'A' && CHESS_ARR[Row][i] <= 'Z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            for (int i = Col + 1; i <= 7; i++) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'A' && CHESS_ARR[Row][i] <= 'Z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col - i < 0) break;
                else if (CHESS_ARR[Row - i][Col - i] == '.') PossibleMoves[(Row - i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row - i][Col - i] >= 'A' && CHESS_ARR[Row - i][Col - i] <= 'Z') {
                    PossibleMoves[(Row - i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col - i < 0) break;
                else if (CHESS_ARR[Row + i][Col - i] == '.') PossibleMoves[(Row + i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row + i][Col - i] >= 'A' && CHESS_ARR[Row + i][Col - i] <= 'Z') {
                    PossibleMoves[(Row + i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col + i >7) break;
                else if (CHESS_ARR[Row - i][Col + i] == '.') PossibleMoves[(Row - i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row - i][Col + i] >= 'A' && CHESS_ARR[Row - i][Col + i] <= 'Z') {
                    PossibleMoves[(Row - i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col + i > 7) break;
                else if (CHESS_ARR[Row + i][Col + i] == '.') PossibleMoves[(Row + i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row + i][Col + i] >= 'A' && CHESS_ARR[Row + i][Col + i] <= 'Z') {
                    PossibleMoves[(Row + i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            break;

        case 'k':
            for (int i = Row - 1; i <= Row + 1; i++)
                for (int j = Col - 1; j <= Col + 1; j++)
                    PossibleMoves[i * 8 + j] = true;
            PossibleMoves[Row * 8 + Col] = false;
            break;

        case 'p':
            // Special case for unmoved pawns
            if (Row == 6 && CHESS_ARR[5][Col] == '.' && CHESS_ARR[4][Col] == '.') PossibleMoves[4 * 8 + Col] = true;
            if (CHESS_ARR[Row + 1][Col] == '.') PossibleMoves[(Row + 1) * 8 + Col] = true;
            if (CHESS_ARR[Row + 1][Col - 1] >= 'A' && CHESS_ARR[Row + 1][Col - 1] <= 'Z')
                PossibleMoves[(Row + 1) * 8 + Col - 1] = true;
            if (CHESS_ARR[Row + 1][Col + 1] >= 'A' && CHESS_ARR[Row + 1][Col + 1] <= 'Z')
                PossibleMoves[(Row + 1) * 8 + Col + 1] = true;
            break;


            //Black
        case 'R':
            for (int i = Row - 1; i >= 0; i--) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'a' && CHESS_ARR[i][Col] <= 'z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Row + 1; i <= 7; i++) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'a' && CHESS_ARR[i][Col] <= 'z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Col - 1; i >= 0; i--) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'a' && CHESS_ARR[Row][i] <= 'z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            for (int i = Col + 1; i <= 7; i++) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'a' && CHESS_ARR[Row][i] <= 'z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            break;

        case 'N':
            if (Row + 2 <= 7 && Col + 1 <= 7 && ((CHESS_ARR[Row + 2][Col + 1] >= 'a' && CHESS_ARR[Row + 2][Col + 1] <= 'z') || CHESS_ARR[Row + 2][Col + 1] == '.'))
                PossibleMoves[(Row + 2) * 8 + Col + 1] = true;
            if (Row + 2 <= 7 && Col - 1 >= 0 && ((CHESS_ARR[Row + 2][Col - 1] >= 'a' && CHESS_ARR[Row + 2][Col - 1] <= 'z') || CHESS_ARR[Row + 2][Col - 1] == '.'))
                PossibleMoves[(Row + 2) * 8 + Col - 1] = true;
            if (Row + 1 <= 7 && Col + 2 <= 7 && ((CHESS_ARR[Row + 1][Col + 2] >= 'a' && CHESS_ARR[Row + 1][Col + 2] <= 'z') || CHESS_ARR[Row + 1][Col + 2] == '.'))
                PossibleMoves[(Row + 1) * 8 + Col + 2] = true;
            if (Row + 1 <= 7 && Col - 2 >= 0 && ((CHESS_ARR[Row + 1][Col - 2] >= 'a' && CHESS_ARR[Row + 1][Col - 2] <= 'z') || CHESS_ARR[Row + 1][Col - 2] == '.'))
                PossibleMoves[(Row + 1) * 8 + Col - 2] = true;
            if (Row - 2 >= 0 && Col + 1 <= 7 && ((CHESS_ARR[Row - 2][Col + 1] >= 'a' && CHESS_ARR[Row - 2][Col + 1] <= 'z') || CHESS_ARR[Row - 2][Col + 1] == '.'))
                PossibleMoves[(Row - 2) * 8 + Col + 1] = true;
            if (Row - 1 >= 0 && Col + 2 <= 7 && ((CHESS_ARR[Row - 1][Col + 2] >= 'a' && CHESS_ARR[Row - 1][Col + 2] <= 'z') || CHESS_ARR[Row - 1][Col + 2] == '.'))
                PossibleMoves[(Row - 1) * 8 + Col + 2] = true;
            if (Row - 2 >= 0 && Col - 1 >= 0 && ((CHESS_ARR[Row - 2][Col - 1] >= 'a' && CHESS_ARR[Row - 2][Col - 1] <= 'z') || CHESS_ARR[Row - 2][Col - 1] == '.'))
                PossibleMoves[(Row - 2) * 8 + Col - 1] = true;
            if (Row - 1 >= 0 && Col - 2 >= 0 && ((CHESS_ARR[Row - 1][Col - 2] >= 'a' && CHESS_ARR[Row - 1][Col - 2] <= 'z') || CHESS_ARR[Row - 1][Col - 2] == '.'))
                PossibleMoves[(Row - 1) * 8 + Col - 2] = true;
            break;

        case 'B':
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col - i < 0) break;
                else if (CHESS_ARR[Row - i][Col - i] == '.') PossibleMoves[(Row - i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row - i][Col - i] >= 'a' && CHESS_ARR[Row - i][Col - i] <= 'z') {
                    PossibleMoves[(Row - i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col - i < 0) break;
                else if (CHESS_ARR[Row + i][Col - i] == '.') PossibleMoves[(Row + i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row + i][Col - i] >= 'a' && CHESS_ARR[Row + i][Col - i] <= 'z') {
                    PossibleMoves[(Row + i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col + i >7) break;
                else if (CHESS_ARR[Row - i][Col + i] == '.') PossibleMoves[(Row - i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row - i][Col + i] >= 'a' && CHESS_ARR[Row - i][Col + i] <= 'z') {
                    PossibleMoves[(Row - i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col + i > 7) break;
                else if (CHESS_ARR[Row + i][Col + i] == '.') PossibleMoves[(Row + i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row + i][Col + i] >= 'a' && CHESS_ARR[Row + i][Col + i] <= 'z') {
                    PossibleMoves[(Row + i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            break;

        case 'Q':
            for (int i = Row - 1; i >= 0; i--) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'a' && CHESS_ARR[i][Col] <= 'z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Row + 1; i <= 7; i++) {
                if (CHESS_ARR[i][Col] == '.') PossibleMoves[i * 8 + Col] = true;
                else if (CHESS_ARR[i][Col] >= 'a' && CHESS_ARR[i][Col] <= 'z') {
                    PossibleMoves[i * 8 + Col] = true;
                    break;
                }
                else break;
            }
            for (int i = Col - 1; i >= 0; i--) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'a' && CHESS_ARR[Row][i] <= 'z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            for (int i = Col + 1; i <= 7; i++) {
                if (CHESS_ARR[Row][i] == '.') PossibleMoves[Row * 8 + i] = true;
                else if (CHESS_ARR[Row][i] >= 'a' && CHESS_ARR[Row][i] <= 'z') {
                    PossibleMoves[Row * 8 + i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col - i < 0) break;
                else if (CHESS_ARR[Row - i][Col - i] == '.') PossibleMoves[(Row - i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row - i][Col - i] >= 'a' && CHESS_ARR[Row - i][Col - i] <= 'z') {
                    PossibleMoves[(Row - i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col - i < 0) break;
                else if (CHESS_ARR[Row + i][Col - i] == '.') PossibleMoves[(Row + i) * 8 + Col - i] = true;
                else if (CHESS_ARR[Row + i][Col - i] >= 'a' && CHESS_ARR[Row + i][Col - i] <= 'z') {
                    PossibleMoves[(Row + i) * 8 + Col - i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row - i < 0 || Col + i >7) break;
                else if (CHESS_ARR[Row - i][Col + i] == '.') PossibleMoves[(Row - i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row - i][Col + i] >= 'a' && CHESS_ARR[Row - i][Col + i] <= 'z') {
                    PossibleMoves[(Row - i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            for (int i = 1; i <= 7; i++) {
                if (Row + i > 7 || Col + i > 7) break;
                else if (CHESS_ARR[Row + i][Col + i] == '.') PossibleMoves[(Row + i) * 8 + Col + i] = true;
                else if (CHESS_ARR[Row + i][Col + i] >= 'a' && CHESS_ARR[Row + i][Col + i] <= 'z') {
                    PossibleMoves[(Row + i) * 8 + Col + i] = true;
                    break;
                }
                else break;
            }
            break;

        case 'K':
            for (int i = Row - 1; i <= Row + 1; i++)
                for (int j = Col - 1; j <= Col + 1; j++)
                    if ((CHESS_ARR[i][j] >= 'a' && CHESS_ARR[i][j] <= 'z') || CHESS_ARR[i][j] == '.') PossibleMoves[i * 8 + j] = true;
            break;

        case 'P':
            // Special case for unmoved pawns
            if (Row == 1 && CHESS_ARR[2][Col] == '.' && CHESS_ARR[3][Col] == '.') PossibleMoves[3 * 8 + Col] = true;
            if (CHESS_ARR[Row + 1][Col] == '.') PossibleMoves[(Row + 1) * 8 + Col] = true;
            if (CHESS_ARR[Row + 1][Col - 1] >= 'a' && CHESS_ARR[Row + 1][Col - 1] <= 'z')
                PossibleMoves[(Row + 1) * 8 + Col - 1] = true;
            if (CHESS_ARR[Row + 1][Col + 1] >= 'a' && CHESS_ARR[Row + 1][Col + 1] <= 'z')
                PossibleMoves[(Row + 1) * 8 + Col + 1] = true;
            break;
    }
    bool* ptr;
    ptr = &PossibleMoves[0];
    return ptr;
}

bool isValidMove(short Move); // Returns whether Move is valid.

void MakeMove(short Move) {  // Make a Move if it is Valid

}


void SetCustom256Color(int ID) {
    cout << "\033[38;5;" << ID << "m";
}

void SetCustomRGBColor(int R, int G, int B) {
    cout << "\033[38;2;" << R << ";" << G << ";" << B << "m";
}

int main() {
    // Loading();
    // Menu();
    _Menu();
    LoadGame("chess.txt");
    // PrintGame();
    _PrintPossibleMoves(AllPossibleMoves(0b1101100000000000));
    // string Move;
    // while (GameState() == 0) {  // If Game is on-going
    //     cin >> Move;
    //     MakeMove(mvHR_Short(Move));
    // }
    // SaveGame("chess2.txt");
    return 0;
}
