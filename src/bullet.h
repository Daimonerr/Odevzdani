#ifndef BULLET_H
#define BULLET_H

#include "obstacleC.h"

/*!
* Inherited class representing bullet
*/
class CBullet : public CObject {
	public:
		
		/*!
		* Constructor that calls CObject constructor
		* @param y Y position of core
		* @param x X position of core
		* @param bChar char that represents core
		*/
		CBullet(const int & y, 
				const int & x, 
				const char & bChar);

		/*!
		* Moves up with bullet 
		* @return True if move was successful
		*/
		virtual bool moveO();

		/*!
		* Tells if object is about to collide
		* @return True bullet cant move further
		*/
		virtual bool isCollision()const;
};

#endif