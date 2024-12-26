/*
 * BcTime.cpp
 *
 *  Created on: Dec 25, 2024
 *      Author: danci
 */

#include "BcGlobals.hpp"
#include "BcTime.hpp"


 int BcTime::GetTime() {
	struct timeb timebuffer;
	ftime(&timebuffer);
	return (timebuffer.time * 1000) + timebuffer.millitm;
}


BcTime::BcTime() {
	// TODO Auto-generated constructor stub

}

BcTime::~BcTime() {
	// TODO Auto-generated destructor stub
}

