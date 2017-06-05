#include "load.h"


LOAD::LOAD(const int & stX, 
		   const int & stTime, 
		   const int & stSpeed, 
		   const char & typeO)
{
	y = 3;
	x = stX;
	time = stTime;
	sp = stSpeed;
	type = typeO;
}