#ifndef OBSTACLEC_H
#define OBSTACLEC_H

#include "obstacleB.h"

/*!
* Inherited class representing obstacle with square move
*/
class CObstacleC : public CObstacle {
	public:

		/*!
		* Constructor calls parental CObstacle constructor
		* @param y Y position of core
		* @param x X position of core
		* @param cChar char that represents core
		* @param sp obstacle speed
		*/
		CObstacleC(const int & y, 
				   const int & x, 
				   const char & cChar, 
				   const int & sp);
		
		/*!
		* Move obstacle in its defined direction
		* @param cntTime object that represents time
		* @return True if move was successful
		*/
		virtual bool moveO(CTimer & cntTime);
	
	private:

		//! variable that play part in obstacle move
		int c_direction;
		
		//! decides which way the obstacle goes
		int c_way;
};

#endif
