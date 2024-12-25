/*
 * BcGame.cpp
 *
 *  Created on: Dec 15, 2024
 *      Author: danci
 */

#include "BcGlobals.hpp"
#include "BcGame.hpp"



BcGame game_list[GAME_STACK];

class BcGame {
public:
	BcGame() {
		// TODO Auto-generated constructor stub

	}

	~BcGame() {
		// TODO Auto-generated destructor stub
	}

	int start;
	int dest;
	int promote;
	int capture;
	int fifty;
	int castle;
	U64 hash;
	U64 lock;


};

