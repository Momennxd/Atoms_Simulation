#pragma once
#include "main_includes.h"

class Glob
{


public:


	static int GetRandomNumber(int from, int to)
	{
		// Generate a random number within the specified range
		int randomNum = from + (std::rand() % (to - from + 1));
		return randomNum;
	}



};