#include<iostream>
using namespace std;

//          Nyx-Chess
// A project by: THE CULT OF THE LINUX
// Authors: IsmailHamza & AwaisTahir
//
// 
// - Run/Test in 9x36 zsh Terminal
// 
// All rights reserved


// Global variables here
char GAME_ARR[8][9];    // The ninth index to store \0
short HIST[4];        // Every move is stored in a 16-bit short. See mvShort_HR
bool SHOW_BOARD_CORD;   // A boolean which when True will show Board co-ordinates
short TIME_INCREMENT;   // The Time to add after every move
short TIME_TOTAL;   // The Total Time alloted to the game
bool SHOW_BOARD_MV; // A boolean which when True shows last move in distint colour
bool SHOW_BOARD_PIECES; // A boolean which when False don't show board pieces aka Blind Fold Chess
short UNICODE_PIECES_PRESET;    // Stores which pre-defined Preset to use, 0 for custom preset; See PC_WT_* and PC_BL_*    
bool SHOW_MV_LST_UNICODE;   // A boolean which when True use Unicode pieces in Last 4 Move list



// The colours of Chess Squaress
char SQ_BG_MV_PRE;
char SQ_BG_MV_NXT;
char SQ_BG_WHITE;
char SQ_BG_BLACK;
char SQ_BG_CUR;
char SQ_FG_MV_PRE;
char SQ_FG_MV_NXT;
char SQ_FG_WHITE;
char SQ_FG_BLACK;
char SQ_FG_CUR;

// Variables to store Pieces
char PC_WT_PAWN;
char PC_WT_ROOK;
char PC_WT_KNIGHT;
char PC_WT_BISHOP;
char PC_WT_QUEEN;
char PC_WT_KING;
char PC_BL_PAWN;
char PC_BL_ROOK;
char PC_BL_KNIGHT;
char PC_BL_BISHOP;
char PC_BL_QUEEN;
char PC_BL_KING;

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





/*
                                    1
                      #             2
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

void NewGame(); // Make a new game a.k.a load default game(call LoadGame with default Path)

void LoadGame(string Path);     // Path to the Game loaded, load it in GAME_ARR Array, extension is ".xchs"

void SaveGame(string Path);     // Path to save game strored GAME_ARR, using ".xchs" extension

int TimePassed();   // Returns curTime - TimeGameStarted

void TimeIncrement();   // Add TIME_INCREMENT to TimeGameStarted (A loop-hole)

int TimeRemaining();    // Returns TIME_TOTAL - TimePassed() , The remaining time is time allowed minus time already passed.

void GamePrint();   // Prints the game stored in GAME_ARR, along with any UI/GUI overlays.

int mvShort_HR(short Move); // Convert short to Human Readable Long Algebraic Notation

int mvHR_Short(short Move); // Convert Human Readable Long Algebraic Notation to short

short* AllPossibleMoves(short Piece);  // Returns an Arr of all possible moves of Piece with first index as len(Arr).

bool isValidMove(short Move); // Returns whether Move is valid.

void MakeMove(short Move);  // Make a Move if it is Valid

int GameState();    // Returns (0, Ongoing); (1, White Won); (2, Black Won); (3, Draw)

int main() {
    Loading();
    Menu();

    return 0;
}
