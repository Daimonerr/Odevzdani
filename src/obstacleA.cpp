#include "obstacleA.h"


CObstacleA::CObstacleA(const int & y, 
					   const int & x, 
					   const char & cChar, 
					   const int & sp): CObstacle(y,x,cChar)
{
	c_obstSpeed = sp;	
	buildOffset(-1,-1, '#');
	buildOffset(-1,0, '#');
	buildOffset(-1,1, '#');
	buildOffset(0,-1, '#');
	buildOffset(0,1, '#');
}


bool CObstacleA::moveO(CTimer & cntTime)
{	
	//! based on ms time and speed calculates when it will move
	if (cntTime.getMsec() % c_obstSpeed == 0 && cntTime.getMsec() != 0)
	{	
		if (isCollision()) 
			return false;
		clearO();
		c_posY++;
		printO();
	}
	return true;
}