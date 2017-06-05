#include "obstacle.h"


CObstacle::CObstacle(const int & y, const int & x, const char & cChar):CObject(y,x,cChar), c_obstSpeed(0)
{}

bool CObstacle::moveO(CTimer & cntTime)
{
	return true;
}


bool CObstacle::isCollision()const
{
	if(c_posY == 44)
	{
		clearO();
		return true;	
	}
	return false;
}


bool CObstacle::collide(const int & y, const int & x)
{
	//! compare with core first
	if (c_posY == y && c_posX == x)
	{
		clearO();
		return true;
	}

	//! compare with other parts (through offset)
	for (int i = 0; i < c_offsLen; i++)
	{
		if ( (c_posY + offset[i].offsY) == y && (c_posX + offset[i].offsX ) == x)
			{
				clearO();
				return true;
			}
	}

	return false;
}