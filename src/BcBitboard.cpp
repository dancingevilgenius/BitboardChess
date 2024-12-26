#include <stdlib.h>
#include <stdint.h>
#include "BcBitboard.hpp"


const BITBOARD debruijn64 = 0x07EDD5E59A4E28C2;

const int index64[NUM_SQUARES] = { 63, 0, 58, 1, 59, 47, 53, 2, 60, 39, 48, 27, 54, 33,
		42, 3, 61, 51, 37, 40, 49, 18, 28, 20, 55, 30, 34, 11, 43, 14, 22, 4,
		62, 57, 46, 52, 38, 26, 32, 41, 50, 36, 17, 19, 29, 10, 13, 21, 56, 45,
		25, 31, 35, 16, 9, 12, 44, 24, 15, 8, 23, 7, 6, 5 };

const int lsb_64_table[NUM_SQUARES] = { 63, 30, 3, 32, 59, 14, 11, 33, 60, 24, 50, 9, 55,
		19, 21, 34, 61, 29, 2, 53, 51, 23, 41, 18, 56, 28, 1, 43, 46, 27, 0, 35,
		62, 31, 58, 4, 5, 49, 54, 6, 15, 52, 12, 40, 7, 42, 45, 16, 25, 57, 48,
		13, 10, 39, 8, 44, 20, 47, 38, 22, 17, 37, 36, 26 };




	void BcBitboard::SetBit(BITBOARD &bb, int square) {
		bb |= (UINT64_C(1) << square);
	}

	void BcBitboard::SetBitFalse(BITBOARD &bb, int square) {
		bb &= ~mask[square];
	}


	// Initialization method
	//@TODO Rename
	void BcBitboard::initSetRowCol() {
		for (int x = 0; x < NUM_SQUARES; x++) {
			if (col[x] < 2)
				SetBit(mask_queenside, x);
			if (col[x] > 5)
				SetBit(mask_kingside, x);
		}

		for (int x = 0; x < NUM_SQUARES; x++)
			for (int y = 0; y < NUM_SQUARES; y++) {
				if (abs(col[x] - col[y]) < 2) {
					if (row[x] < row[y] && row[y] < 7)
						SetBit(mask_passed[0][x], y);
					if (row[x] > row[y] && row[y] > 0)
						SetBit(mask_passed[1][x], y);
				}
				if (abs(col[x] - col[y]) == 1) {
					SetBit(mask_isolated[x], y);
				}
				if (col[x] == col[y]) {
					if (row[x] < row[y])
						SetBit(mask_path[0][x], y);
					if (row[x] > row[y])
						SetBit(mask_path[1][x], y);
				}
			}

	}





	//x & ~(x-1)
	//c & -c or c & (~c + 1) from bitwise tricks


	// @TODO Rename to Initialize
	void BcBitboard::initSetBits() {
		initSetRanks();
		initSetRowCol();

		// Set all of the following bitboards to zero/empty
		memset(bit_pawncaptures, 0, sizeof(bit_pawncaptures));
		memset(bit_pawnmoves, 0, sizeof(bit_pawnmoves));
		memset(bit_knightmoves, 0, sizeof(bit_knightmoves));
		memset(bit_bishopmoves, 0, sizeof(bit_bishopmoves));
		memset(bit_rookmoves, 0, sizeof(bit_rookmoves));
		memset(bit_queenmoves, 0, sizeof(bit_queenmoves));
		memset(bit_kingmoves, 0, sizeof(bit_kingmoves));

		// In Bitboard Chess Engine this for loop is extracted into SetPawnBits() function
		for (int x = 0; x < NUM_SQUARES; x++) {
			SetBit(mask[x], x);
			not_mask[x] = ~mask[x];

			pawnleft[0][x] = -1;
			pawnleft[1][x] = -1;
			pawnright[0][x] = -1;
			pawnright[1][x] = -1;
			if (col[x] > 0) {
				if (row[x] < 7) {
					pawnleft[0][x] = x + 7;
				}
				if (row[x] > 0) {
					pawnleft[1][x] = x - 9;
				}
			}
			if (col[x] < 7) {
				if (row[x] < 7) {
					pawnright[0][x] = x + 9;
				}
				if (row[x] > 0) {
					pawnright[1][x] = x - 7;
				}
			}
			if (col[x] > 0) {
				if (row[x] < 7) {
					SetBit(bit_pawncaptures[0][x], pawnleft[0][x]);
					SetBit(bit_left[0][x], pawnleft[0][x]);
				}
				if (row[x] > 0) {
					SetBit(bit_pawncaptures[1][x], pawnleft[1][x]);
					SetBit(bit_left[1][x], pawnleft[1][x]);
				}
			}
			if (col[x] < 7) {
				if (row[x] < 7) {
					SetBit(bit_pawncaptures[0][x], pawnright[0][x]);
					SetBit(bit_right[0][x], pawnright[0][x]);
				}
				if (row[x] > 0) {
					SetBit(bit_pawncaptures[1][x], pawnright[1][x]);
					SetBit(bit_right[1][x], pawnright[1][x]);
				}
			}
			bit_pawndefends[0][x] = bit_pawncaptures[1][x];
			bit_pawndefends[1][x] = bit_pawncaptures[0][x];

			if (row[x] < 7)
				pawnplus[0][x] = x + 8;
			if (row[x] < 6)
				pawndouble[0][x] = x + 16;
			if (row[x] > 0)
				pawnplus[1][x] = x - 8;
			if (row[x] > 1)
				pawndouble[1][x] = x - 16;
		}

		for (int x = 0; x < NUM_SQUARES; x++)
			for (int y = 0; y < NUM_SQUARES; y++) {
				if (col[x] == col[y])
					SetBit(mask_cols[x], y);
			}

		initSetBetweenVector();

		not_a_file = ~mask_cols[0];
		not_h_file = ~mask_cols[7];
	}

	// Initialization method
	// @TODO rename
	void BcBitboard::initSetBetweenVector() {
		int x, y;
		int z;
		for (x = 0; x < NUM_SQUARES; x++)
			for (y = 0; y < NUM_SQUARES; y++) {
				if (row[x] == row[y]) {
					if (y > x)
						for (z = x + 1; z < y; z++)
							SetBit(bit_between[x][y], z);
					else
						for (z = y + 1; z < x; z++)
							SetBit(bit_between[x][y], z);
				}

				if (col[x] == col[y]) {
					if (y > x)
						for (z = x + 8; z < y; z += 8)
							SetBit(bit_between[x][y], z);
					else
						for (z = y + 8; z < x; z += 8)
							SetBit(bit_between[x][y], z);
				}

				if (nwdiag[x] == nwdiag[y]) {
					if (y > x)
						for (z = x + 7; z < y; z += 7)
							SetBit(bit_between[x][y], z);
					else
						for (z = y + 7; z < x; z += 7)
							SetBit(bit_between[x][y], z);
				}

				if (nediag[x] == nediag[y]) {
					if (y > x)
						for (z = x + 9; z < y; z += 9)
							SetBit(bit_between[x][y], z);
					else
						for (z = y + 9; z < x; z += 9)
							SetBit(bit_between[x][y], z);
				}
			}

		for (x = 0; x < NUM_SQUARES; x++)
			for (y = 0; y < NUM_SQUARES; y++) {
				if (row[x] == row[y]) {
					if (y > x)
						for (z = x + 1; z <= y; z++)
							SetBit(vectorbits[x][y], z);
					else
						for (z = y; z < x; z++)
							SetBit(vectorbits[x][y], z);
				}

				if (col[x] == col[y]) {
					if (y > x)
						for (z = x + 8; z <= y; z += 8)
							SetBit(vectorbits[x][y], z);
					else
						for (z = y; z < x; z += 8)
							SetBit(vectorbits[x][y], z);
				}

				if (nwdiag[x] == nwdiag[y]) {
					if (y > x)
						for (z = x + 7; z <= y; z += 7)
							SetBit(vectorbits[x][y], z);
					else
						for (z = y; z < x; z += 7)
							SetBit(vectorbits[x][y], z);
				}

				if (nediag[x] == nediag[y]) {
					if (y > x)
						for (z = x + 9; z <= y; z += 9)
							SetBit(vectorbits[x][y], z);
					else
						for (z = y; z < x; z += 9)
							SetBit(vectorbits[x][y], z);
				}

			}
		for (x = 0; x < NUM_SQUARES; x++) {
			mask_vectors[x][NORTH] = vectorbits[x][56 + col[x]];
			mask_vectors[x][SOUTH] = vectorbits[x][col[x]];
			mask_vectors[x][WEST] = vectorbits[x][row[x] * 8];
			mask_vectors[x][EAST] = vectorbits[x][row[x] * 8 + 7];
			if (col[x] > 0 && row[x] < 7)
				mask_vectors[x][NW] = vectorbits[x][GetEdge(x, EdgeDir::DIR_NW)];
			if (col[x] < 7 && row[x] < 7)
				mask_vectors[x][NE] = vectorbits[x][GetEdge(x, EdgeDir::DIR_NE)];
			if (row[x] > 0 && col[x] > 0)
				mask_vectors[x][SW] = vectorbits[x][GetEdge(x, EdgeDir::DIR_SW)];
			if (row[x] > 0 && col[x] < 7)
				mask_vectors[x][SE] = vectorbits[x][GetEdge(x, EdgeDir::DIR_SE)];
		}

	}


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
	int BcBitboard::GetEdge(int sq, EdgeDir dir) {
		do {
			sq += dir;
		} while (col[sq] > 0 && col[sq] < 7 && row[sq] > 0 && row[sq] < 7);

		return sq;
	}

	// Initialization method
	//@TODO Rename
	void BcBitboard::initSetRanks() {
		for (int x = 0; x < NUM_SQUARES; x++) {
			rank[SIDE_WHITE][x] = row[x];
			rank[SIDE_BLACK][x] = 7 - row[x];
		}
	}

	/* debruin
	 int bitScanForward(U64 bb)
	 {
	 const U64 debruijn64 = C64(0x03f79d71b4cb0a89);
	 assert (bb != 0);
	 return index64[((bb & -bb) * debruijn64) >> 58];
	 }
	 */
	/*
	 int NextBit(BITBOARD bb)
	 {
	 if(bb==0)return 0;//
	 const unsigned int debruijn64 = 0x03f79d71b4cb0a89;
	 //assert (bb != 0);
	 int x = index64[((bb & -bb) * debruijn64) >> 58];
	 if(x<0 || x>63)
	 return 0;

	 return x;
	 }
	 //*/
	//*
	int BcBitboard::NextBit(BITBOARD bb) //folded - used for ages
			{
		unsigned int folded;
		//assert (bb != 0);
		bb ^= bb - 1;
		folded = (int) bb ^ (bb >> 32);
		return lsb_64_table[folded * 0x78291ACF >> 26];
	}

	int BcBitboard::NextBit2(BITBOARD bb) //number 2  crashed
			{
		if (bb == 0)
			return 0;
		const BITBOARD debruijn64 = (unsigned char) (0x03f79d71b4cb0a89);
	//   assert (bb != 0);
		return index64[((bb ^ (bb - 1)) * debruijn64) >> 58];
	}

	void BcBitboard::PrintBitBoard(BITBOARD bb) {
		printf("\n");
		int x;
		for (x = 56; x < NUM_SQUARES; x++)
			PrintCell(x, bb);
		for (x = 48; x < 56; x++)
			PrintCell(x, bb);
		for (x = 40; x < 48; x++)
			PrintCell(x, bb);
		for (x = 32; x < 40; x++)
			PrintCell(x, bb);
		for (x = 24; x < 32; x++)
			PrintCell(x, bb);
		for (x = 16; x < 24; x++)
			PrintCell(x, bb);
		for (x = 8; x < 16; x++)
			PrintCell(x, bb);
		for (x = 0; x < 8; x++)
			PrintCell(x, bb);
	}

	void BcBitboard::PrintCell(int x, BITBOARD bb) {
		if (mask[x] & bb)
			printf(" X");
		else
			printf(" -");
		if ((x + 1) % 8 == 0)
			printf("\n");
	}


/*
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

*/







