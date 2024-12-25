#pragma once
/*
 * BcAttack.hpp
 *
 *  Created on: Dec 15, 2024
 *      Author: danci
 */


#include "BcGlobals.hpp"
#include "BcBitboard.hpp"



class BcAttack {
public:
	BcAttack();
	virtual ~BcAttack();


	/*

	 Attack returns true if one side attacks a given square and false if it doesn't.
	 It is used to tell if a King is in check, but can have other uses.

	 */
	bool Attack(BcBitboard &bb, const int s, const int sq);

	/*

	 LowestAttacker is similar to Attack. It returns the square the weakest attacker of the given side and given square.
	 It returns -1 if there are no attackers.
	 It is used to find the next piece that will recapture, but can have other uses.

	 */
	int LowestAttacker(BcBitboard &bb, const int s, const int xs, const int sq);

};

