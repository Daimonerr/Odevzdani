#include "obstacleC.h"

CObstacleC::CObstacleC(const int & y, 
					   const int & x, 
					   const char & cChar, 
					   const int & sp): CObstacle(y,x,cChar), c_direction(0), c_way(0)
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


bool CObstacleC::moveO(CTimer & cntTime)
{	
	//! based on ms time and speed calculates when it will move
	if (cntTime.getMsec() % c_obstSpeed == 0 && cntTime.getMsec() != 0)
	{	
		if (isCollision())
			return false;		
		clearO();

		switch (c_way)
		{
		case 0:
			c_posY++;
			break;
		case 1:
			c_posX++;
			break;
		case 2:
			c_posY++;
			break;	
		case 3:
			c_posX--;
			break;
		}

		//! helps to reset c_way so it is periodical
		c_direction++;
		if (c_direction % 4 == 0){
			c_way++; c_direction=0;
		}
			
		if (c_way == 4)
			c_way=0;

		printO();
	}
	
	return true;
}