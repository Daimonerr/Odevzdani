#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "object.h"

/*!
* Inherited (and also parental) class representing obstacle
*/
class CObstacle : public CObject {
	public:

		/*!
		* Constructor calls parental CObstacle constructor
		* @param y Y position of core
		* @param x X position of core
		* @param cChar char that represents core
		*/
		CObstacle(const int & y, 
				  const int & x, 
				  const char & cChar);

		/*!
		* Virtual destructor
		*/
		virtual ~CObstacle(){};

		/*!
		* Move with obstacle in its direction, always returns true(not in inherited classes)
		* @param cntTime object that represents time
		* @return True if move was successful
		*/
		virtual bool moveO(CTimer & cntTime);

		/*!
		* Returns true if obstacle is about to fly out of the map
		* @return True if obstacle cant move further
		*/
		virtual bool isCollision()const;

		/*!
		* Compare inserted positions with all obstacles points, returns true if equal
		* @param y Y position
		* @param x X position 
		* @return True if y and x matches with collision points of obstacle  
		*/
		bool collide(const int & y, 
					 const int & x);
	
	protected:
		
		//! decides how fast will obstacle move
		int c_obstSpeed;
};

#endif
