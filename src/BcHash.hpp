#pragma once
/*
 * BcHash.hpp
 *
 *  Created on: Dec 23, 2024
 *      Author: danci
 */

#include "BcGlobals.hpp"
#include "BcMove.hpp"


const U64 MAXHASH = 5000000;
const U64 HASHSIZE = 5000000;


class BcHashP {
public:
	U64 hashlock;
	int start;
	int dest;
	int num;

	// Below this line are vars copied here by Carlos
	BcHashP *hashpos[2];

	const U64 MAXHASH = 5000000;
	const U64 HASHSIZE = 5000000;

	int hash_start, hash_dest;

	void RandomizeHash();
	int Random(const int x);
	void Free();
	bool LookUp(const int s);
	U64 Random2(int x);
	U64 GetKey();
	U64 GetLock();
	void AddKey(const int s, const int p, const int x);
	void AddHash(const int s, const BcMove m);

};
