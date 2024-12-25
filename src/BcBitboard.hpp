#pragma once

#include "BcGlobals.hpp"


// Used only in GetEdge()
//Plus Adding 1 moves right.
//Subtracting 1 moves left.
//Adding 8 moves up.
//Subtracting 8 moves down.
//Adding 7 moves up and left.
//Subtracting 9 moves down and left.
//Adding 9 moves up and right.
//Subtracting 7 moves down and right.
enum EdgeDir {
  DIR_E=1,
  DIR_W=-1,
  DIR_N=8,
  DIR_S=-8,
  DIR_NW=7,
  DIR_SW=-9,
  DIR_NE=9,
  DIR_SE=-7

};


class BcBitboard {
	public:

	void SetBit(BITBOARD &bb, int square);

	void SetBitFalse(BITBOARD &bb, int square);

	// Initialization method
	//@TODO Rename
	void SetRowCol();





	// @TODO Rename to Initialize
	void SetBits();

	// Initialization method
	// @TODO rename
	void SetBetweenVector();

	//returns the edge square when moving in a certain direction. There are 8 possible directions from a square.
	//
	//Plus Adding 1 moves right.
	//Subtracting 1 moves left.
	//Adding 8 moves up.
	//Subtracting 8 moves down.
	//Adding 7 moves up and left.
	//Subtracting 9 moves down and left.
	//Adding 9 moves up and right.
	//Subtracting 7 moves down and right.

	// @TODO rename getEdgeSquare.
	int GetEdge(int sq, EdgeDir dir);

	// Initialization method
	//@TODO Rename
	void SetRanks();

	static int NextBit(BITBOARD bb);
	int NextBit2(BITBOARD bb);

	void PrintBitBoard(BITBOARD bb);

	void PrintCell(int x, BITBOARD bb);


	public:
		BITBOARD bit_pawncaptures[NUM_SIDES][NUM_SQUARES];
		BITBOARD bit_pawndefends[NUM_SIDES][NUM_SQUARES];
		BITBOARD bit_left[NUM_SIDES][NUM_SQUARES];
		BITBOARD bit_right[NUM_SIDES][NUM_SQUARES];

		BITBOARD bit_pawnmoves[NUM_SIDES][NUM_SQUARES];
		BITBOARD bit_knightmoves[NUM_SQUARES];
		BITBOARD bit_bishopmoves[NUM_SQUARES];
		BITBOARD bit_rookmoves[NUM_SQUARES];
		BITBOARD bit_queenmoves[NUM_SQUARES];
		BITBOARD bit_kingmoves[NUM_SQUARES];

		BITBOARD bit_pieces[NUM_SIDES][NUM_PIECES];
		BITBOARD bit_units[NUM_SIDES];
		BITBOARD bit_all;

		BITBOARD bit_between[NUM_SQUARES][NUM_SQUARES];
		BITBOARD vectorbits[NUM_SQUARES][NUM_SQUARES];
		BITBOARD mask_vectors[NUM_SQUARES][NUM_DIRECTIONS];

		BITBOARD mask_passed[NUM_SIDES][NUM_SQUARES];
		BITBOARD mask_path[NUM_SIDES][NUM_SQUARES];

		BITBOARD mask[NUM_SQUARES];
		BITBOARD not_mask[NUM_SQUARES];
		BITBOARD mask_cols[NUM_SQUARES];
		BITBOARD mask_isolated[NUM_SQUARES];

		BITBOARD mask_kingside;
		BITBOARD mask_queenside;
		BITBOARD not_a_file;
		BITBOARD not_h_file;

		int pawnplus[NUM_SIDES][NUM_SQUARES];
		int pawndouble[NUM_SIDES][NUM_SQUARES];
		int pawnleft[NUM_SIDES][NUM_SQUARES];
		int pawnright[NUM_SIDES][NUM_SQUARES];

};





