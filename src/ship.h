#ifndef SHIP_H
#define SHIP_H

#include "bullet.h"

/*!
* Inherited class representing flying ship
*/
class CShip : public CObject {
	public:
		
		/*!
		* Constructor initializing offset of ship
		*/
		CShip();

		/*!
		* Makes new bullet
		* @return Returns bullet with posY and posX of main gun
		*/
		CBullet newBullet();

		/*!
		* Makes new bullet dependable on offsets
		* @param offsetY offset Y from core of the ship
		* @param offsetX offset X from core of the ship
		* @return Returns bullet with posY+offsetY and posX+offsetX
		*/
		CBullet newBullet(const int & offsetY, 
						  const int & offsetX);

		/*!
		* Changes X position of core by -2
		*/
		void moveLeft();

		/*!
		* Changes X position of core by 2
		*/
		void moveRight();

		/*!
		* Changes Y position of core by -1
		*/
		void moveUp();

		/*!
		* Changes Y position of core by 1
		*/
		void moveDown();

		/*!
		* Blind method
		* @return Always returns false, not used, used for obstacles
		*/
		virtual bool isCollision()const;
};

#endif