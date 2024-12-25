#include <memory.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <direct.h>
#include <time.h>


void ShowAll(int ply);

#define U64 unsigned __int64 
#define BITBOARD unsigned __int64 


// Start Added by Carlos ----------------------------------------------------
#define NUM_SQUARES 64
#define NUM_SIDES 2
// End Added by Carlos  ------------------------------------------------------

#define A1	0
#define B1	1
#define C1	2
#define D1	3
#define E1	4
#define F1  5
#define G1	6
#define H1	7

#define A2	8
#define B2	9
#define C2	10
#define D2	11
#define E2	12
#define F2	13
#define G2	14
#define H2	15

#define A3	16
#define B3	17
#define C3	18
#define D3	19
#define E3	20
#define F3	21
#define G3	22
#define H3	23

#define A4	24
#define B4	25
#define C4	26
#define D4	27
#define E4	28
#define F4	29
#define G4	30
#define H4	31

#define A5	32
#define B5	33
#define C5	34
#define D5	35
#define E5	36
#define F5	37
#define G5	38
#define H5	39

#define A6	40
#define B6	41
#define C6	42
#define D6	43
#define E6	44
#define F6	45
#define G6	46
#define H6	47

#define A7	48
#define B7	49
#define C7	50
#define D7	51
#define E7	52
#define F7	53
#define G7	54
#define H7	55

#define A8	56
#define B8	57
#define C8	58
#define D8	59
#define E8	60
#define F8	61
#define G8	62
#define H8	63

#define NORTH 0
#define NE 1
#define EAST 2
#define SE 3
#define SOUTH 4
#define SW 5
#define WEST 6
#define NW 7
#define NUM_DIRECTIONS 8 // Added by Carlos

#define P 0
#define N 1
#define B 2
#define R 3
#define Q 4
#define K 5
#define EMPTY 6
#define NUM_PIECES 7// Added by Carlos

#define White 0
#define Black 1

#define MAX_PLY 64
#define MOVE_STACK 4000
#define GAME_STACK 2000

#define HASH_SCORE    100000000
#define CAPTURE_SCORE 10000000



extern int piece_value[6];
extern int pawn_mat[NUM_SIDES];
extern int piece_mat[NUM_SIDES];

extern int king_endgame[NUM_SIDES][NUM_SQUARES];
extern int passed[NUM_SIDES][NUM_SQUARES];

extern char piece_char[6];

extern int side, xside;
extern int fifty;
extern int ply, hply;
extern int castle;
extern int castle_mask[NUM_SQUARES];

extern int nodes;

extern int board[NUM_SQUARES];
extern int init_color[NUM_SQUARES];
extern int init_board[NUM_SQUARES];

extern int history[NUM_SQUARES][NUM_SQUARES];

extern int square_score[NUM_SIDES][6][NUM_SQUARES];

extern const int row[NUM_SQUARES];
extern const int col[NUM_SQUARES];
extern const int nwdiag[NUM_SQUARES];
extern const int nediag[NUM_SQUARES];

extern int first_move[MAX_PLY];
//extern BcMove move_list[MOVE_STACK];
//extern BcGame game_list[GAME_STACK];

extern int hash_start, hash_dest;
extern U64 currentkey, currentlock;

extern int fixed_time;
extern int fixed_depth;
extern int max_time;
extern int start_time;
extern int stop_time;
extern int max_depth;

extern int qrb_moves[NUM_SQUARES][9];
extern int knight_moves[NUM_SQUARES][9];
extern int king_moves[NUM_SQUARES][9];

extern U64 collisions;

extern int turn;

extern int Flip[NUM_SQUARES];

extern int rank[NUM_SIDES][NUM_SQUARES];

extern U64 vectorbits[NUM_SQUARES][NUM_SQUARES];
extern U64 mask_vectors[NUM_SQUARES][NUM_DIRECTIONS];
extern BITBOARD bit_between[NUM_SQUARES][NUM_SQUARES];
extern int pawndouble[NUM_SIDES][NUM_SQUARES];
extern int pawnplus[NUM_SIDES][NUM_SQUARES];
extern int pawnleft[NUM_SIDES][NUM_SQUARES];
extern int pawnright[NUM_SIDES][NUM_SQUARES];

extern BITBOARD bit_pawncaptures[NUM_SIDES][NUM_SQUARES];
extern BITBOARD bit_pawndefends[NUM_SIDES][NUM_SQUARES];
extern BITBOARD bit_left[NUM_SIDES][NUM_SQUARES];
extern BITBOARD bit_right[NUM_SIDES][NUM_SQUARES];
extern BITBOARD bit_pawnmoves[NUM_SIDES][NUM_SQUARES];
extern BITBOARD bit_knightmoves[NUM_SQUARES];
extern BITBOARD bit_bishopmoves[NUM_SQUARES];
extern BITBOARD bit_rookmoves[NUM_SQUARES];
extern BITBOARD bit_queenmoves[NUM_SQUARES];
extern BITBOARD bit_kingmoves[NUM_SQUARES];

//current position
extern BITBOARD bit_pieces[NUM_SIDES][NUM_PIECES];
extern BITBOARD bit_units[NUM_SIDES];
extern BITBOARD bit_all;

extern BITBOARD mask_passed[NUM_SIDES][NUM_SQUARES];
extern BITBOARD mask_path[NUM_SIDES][NUM_SQUARES];

extern BITBOARD mask_cols[NUM_SQUARES];

extern BITBOARD mask[NUM_SQUARES];
extern BITBOARD not_mask[NUM_SQUARES];

extern BITBOARD mask_isolated[NUM_SQUARES];

extern BITBOARD not_a_file;
extern BITBOARD not_h_file;


