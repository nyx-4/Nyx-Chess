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
// Authors: IsmailHamza & AwaisTahir
//
// 
// - Run/Test in 9x36 zsh Terminal
// 
// All rights reserved



#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

// Global variables here
char CHESS_ARR[8][9];    // The ninth index to store \0
short HIST[4];        // Every move is stored in a 16-bit short. See mvShort_HR
bool SHOW_BOARD_CORD;   // A boolean which when True will show Board co-ordinates
long int TIME_INCREMENT;   // The Time to add after every move
long int TIME_TOTAL;   // The Total Time alloted to the game
long int TIME_GAME_STARTED;    // The time the game started
int MOVES_MADE_WHITE = 0;
int MOVES_MADE_BLACK = 0;
bool SHOW_BOARD_MV; // A boolean which when True shows last move in distint colour
bool SHOW_BOARD_PIECES; // A boolean which when False don't show board pieces aka Blind Fold Chess
short UNICODE_PIECES_PRESET;    // Stores which pre-defined Preset to use, 0 for custom preset; See PC_WT_* and PC_BL_*    
bool SHOW_MV_LST_UNICODE;   // A boolean which when True use Unicode pieces in Last 4 Move list

// The Rules for GAME_ARR
// (p, pawn); (r, rook); (n, knight); (b, bishop); (q, queen); (k, king); (. for empty square);
// Capital for Black and small for White.


// Basic Escape sequences
string RESET = "\033[0m";

string FG_BLACK = "\033[30m";
string FG_RED = "\033[31m";
string FG_GREEN = "\033[32m";
string FG_YELLOW = "\033[33m";
string FG_BLUE = "\033[34m";
string FG_MAGENTA = "\033[35m";
string FG_CYAN = "\033[36m";
string FG_WHITE = "\033[37m";
string FG_DEFAULT = "\033[39m";

string BG_BLACK = "\033[40m";
string BG_RED = "\033[41m";
string BG_GREEN = "\033[42m";
string BG_YELLOW = "\033[43m";
string BG_BLUE = "\033[44m";
string BG_MAGENTA = "\033[45m";
string BG_CYAN = "\033[46m";
string BG_WHITE = "\033[47m";
string BG_DEFAULT = "\033[49m";

string BRIGHT = "\033[1m";
string BOLD = "\033[1m";
string DIM = "\033[2m";
string ITALIC = "\033[3m";
string UNDERLINE = "\033[4m";
string BLINK = "\033[5m";
string REVERSE = "\033[7m";
string HIDDEN = "\033[8m";
string STRIKETHROUGH = "\033[9m";


// The colours of Chess Squares, store as ";R;G;B" or ";ID" or "\033[3.m"
string SQ_BG_MV_PRE;
string SQ_BG_MV_NXT;
string SQ_BG_WHITE;
string SQ_BG_BLACK;
string SQ_BG_CUR;
string SQ_FG_MV_PRE;
string SQ_FG_MV_NXT;
string SQ_FG_WHITE;
string SQ_FG_BLACK;
string SQ_FG_CUR;

// Variables to store Pieces
string PC_WT_PAWN;
string PC_WT_ROOK;
string PC_WT_KNIGHT;
string PC_WT_BISHOP;
string PC_WT_QUEEN;
string PC_WT_KING;
string PC_BL_PAWN;
string PC_BL_ROOK;
string PC_BL_KNIGHT;
string PC_BL_BISHOP;
string PC_BL_QUEEN;
string PC_BL_KING;
string PC_EMPTY;

// The navigation Keys, use WT* for White and BL* for Blacks
char WT_UP;
char WT_DN;
char WT_RT;
char WT_LF;
char WT_SELECT;
char BL_UP;
char BL_DN;
char BL_RT;
char BL_LF;
char BL_SELECT;

// A place for local functions

void _Menu() { // A dummy Menu to test variables, final values should be assigned in Menu()
    SQ_BG_BLACK = BG_BLACK;
    SQ_BG_WHITE = BG_WHITE;
    PC_WT_PAWN = "P";
    PC_WT_ROOK = "P";
    PC_WT_KNIGHT = "P";
    PC_WT_BISHOP = "P";
    PC_WT_QUEEN = "P";
    PC_WT_KING = "P";
    PC_BL_PAWN = "P";
    PC_BL_ROOK = "P";
    PC_BL_KNIGHT = "P";
    PC_BL_BISHOP = "P";
    PC_BL_QUEEN = "P";
    PC_BL_KING = "P";
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

bool isCheck(); // Returns whether its check or not.

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
    if (isCheck()) CHK = "+";
    return IC + IR + XS + FC + FR + "=" + PP + CHK;
}

short mvHR_Short(string mv) {  // Convert Human Readable Long Algebraic Notation to short
    int PR = 0;
    switch (mv[6]) {
        case ' ': PR = 0; break;
        case 'R': PR = 1; break;
        case 'N': PR = 2; break;
        case 'B': PR = 3; break;
        case 'Q': PR = 4; break;
    }
    return (mv[0] - 65) * 8192 + (mv[1] - 48) * 1024 + (mv[3] - 65) * 128 + (mv[4] - 48) * 16 + PR * 2 + ((mv[2] == 'x') ? 1 : 0);
}

short* AllPossibleMoves(short Piece);  // Returns an Arr of all possible moves of Piece with first index as len(Arr).

bool isValidMove(short Move); // Returns whether Move is valid.

void MakeMove(short Move);  // Make a Move if it is Valid

int GameState();    // Returns (0, Ongoing); (1, White Won); (2, Black Won); (3, Draw)

void SetCustom256Color(int ID) {
    cout << "\033[38;5;" << ID << "m";
}

void SetCustomRGBColor(int R, int G, int B) {
    cout << "\033[38;2;" << R << ";" << G << ";" << B << "m";
}

int main() {
    // Loading();
    // Menu();
    // _Menu();
    // LoadGame("chess.txt");
    // PrintGame();
    // SaveGame("chess2.txt");
    return 0;
}
