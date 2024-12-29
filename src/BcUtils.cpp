/*
 * BcUtils.cpp
 *
 *  Created on: Dec 28, 2024
 *      Author: danci
 */

#include "BcUtils.h"

BcUtils::BcUtils() {
	// TODO Auto-generated constructor stub

}

BcUtils::~BcUtils() {
	// TODO Auto-generated destructor stub
}




void BcUtils::Alg(int a, int b) {
	Algebraic(a);
	Algebraic(b);
}
/*

 Algebraic displays a square.
 e.g. 3 becomes col[3] + 96 which is ascii character 'd' and row[3]+1 which is '1'.
 Passing 3 returns 'd1'.

 */
void BcUtils::Algebraic(int a) {
	if (a < 0 || a > 63)
		return;
	char c[2] = "a";
	c[0] = 96 + 1 + col[a];
	printf("%s%d", c, row[a] + 1);
}



/*

 Alg displays a move.

 */
void BcUtils::Alg(int a, int b) {
	Algebraic(a);
	Algebraic(b);
}

