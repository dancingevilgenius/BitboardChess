#pragma once
/*
 * BcSearch.hpp
 *
 *  Created on: Dec 25, 2024
 *      Author: danci
 */

class BcSearch {
public:

	void think();
	void CheckUp();
	int Search(int alpha, int beta, int depth);
	int CaptureSearch(int alpha, int beta);
	int ReCaptureSearch(int a, const int sq);
	int reps2();
	void Sort(const int from);
	void DisplayPV(int i);
	void SetHashMove();
};
