#pragma once


/*
 * BcGen.hpp
 *
 *  Created on: Dec 24, 2024
 *      Author: danci
 */

class BcGen {
public:

	int px[6] = { 0, 10, 20, 30, 40, 0 };
	int nx[6] = { -3, 7, 17, 27, 37, 0 };
	int bx[6] = { -3, 7, 17, 27, 37, 0 };
	int rx[6] = { -5, 5, 15, 25, 35, 0 };
	int qx[6] = { -9, 1, 11, 21, 31, 0 };
	int kx[6] = { 0, 10, 20, 30, 40, 0 };

	int mc;
	int castle;


	void Gen(const int s, const int sx);
	void AddMove(const int x, const int sq);
	void AddCapture(const int x, const int sq, const int score);


};
