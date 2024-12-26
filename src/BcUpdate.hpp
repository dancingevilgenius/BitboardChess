#pragma once
/*
 * BcUpdate.hpp
 *
 *  Created on: Dec 25, 2024
 *      Author: danci
 */


class BcUpdate {
public:
	BcUpdate();
	virtual ~BcUpdate();


	void UpdatePiece(const int s, const int p, const int start, const int dest);

	void AddPiece(const int s, const int p, const int sq);
	int MakeMove(const int start, const int dest);
	void TakeBack();
	void UnMakeRecapture();
};

