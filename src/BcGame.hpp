/*
 * BcGame.hpp
 *
 *  Created on: Dec 15, 2024
 *      Author: danci
 */
#include "BcGlobals.hpp"

#ifndef BCGAME_HPP_
#define BCGAME_HPP_

class BcGame {
public:
	BcGame();
	virtual ~BcGame();
	int start;
	int dest;
	int promote;
	int capture;
	int fifty;
	int castle;
	U64 hash;
	U64 lock;
};

#endif /* BCGAME_HPP_ */
