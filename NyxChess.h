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
// A project by: Ismail Hamza
// Authors: IsmailHamza & AwaisTahir
//
// 
// - Run/Test in 9x36 zsh Terminal
// 
// All rights reserved


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
string SQ_BG_YELLOW;
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

bool* AllPossibleMoves(short);