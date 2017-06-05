#include "obstacleB.h"

CObstacleB::CObstacleB(const int & y, 
					   const int & x, 
					   const char & cChar, 
					   const int & sp): CObstacle(y,x,cChar), c_direction(0), c_flip(1)
{
	c_obstSpeed = sp;
	buildOffset(-2,-1, '/');
	buildOffset(-2,0, '#');
	buildOffset(-2,1, '\\');
	buildOffset(-1,-1, '#');
	buildOffset(-1,0, '#');
	buildOffset(-1,1, '#');
	buildOffset(0,-1, '\\');
	buildOffset(0,1, '/');
}


bool CObstacleB::moveO(CTimer & cntTime)
{	
	//! based on ms time and speed calculates when it will move
	if (cntTime.getMsec() % c_obstSpeed == 0 && cntTime.getMsec() != 0)
	{	
		if (isCollision())
			return false;
		
		clearO();

			if (c_flip == 1 )
				c_posX++;
			else
				c_posX--;

			c_posY++;

		printO();

		//! changing c_flip 
		c_direction++;
		if (c_direction == 3 && c_flip == 1)
		{
			c_direction = 0;
			c_flip=0;
		}

		if (c_direction == 3 && c_flip == 0)
		{
			c_direction = 0;
			c_flip=1;
		}
	}
	
	return true;
}