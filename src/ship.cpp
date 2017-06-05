#include "ship.h"

CShip::CShip ():CObject(41,28,'A')
{
	//! builds visual view of ship around the core of object
	buildOffset(-1,-1,'/');
	buildOffset(-1,1,'\\');
	buildOffset(-1,0,'|');

	buildOffset(0,-2,'/');
	buildOffset(0,-1,'#');
	buildOffset(0,1,'#');
	buildOffset(0,2,'\\');

	buildOffset(1,3,'/');
	buildOffset(1,2,'/');
	buildOffset(1,1,'O');
	buildOffset(1,0,'|');
	buildOffset(1,-1,'O');
	buildOffset(1,-2,'\\');
	buildOffset(1,-3,'\\');

	buildOffset(2,3,'^');
	buildOffset(2,2,'^');
	buildOffset(2,1,'^');
	buildOffset(2,0,'^');
	buildOffset(2,-1,'^');
	buildOffset(2,-2,'^');
	buildOffset(2,-3,'^');
}

CBullet CShip::newBullet()
{
	CBullet newB(c_posY-2, c_posX, '*');

	return newB;
}

CBullet CShip::newBullet(const int & offsetY, const int & offsetX)
{
	CBullet newB(c_posY+offsetY, c_posX+offsetX, '*');

	return newB;
}

void CShip::moveLeft()
{
	if (c_posX - 3 == 1 )
		return;
	c_posX -= 2;
}

void CShip::moveRight()
{
	if (c_posX + 3 == 59 )
		return;
	c_posX += 2;
}

void CShip::moveUp()
{
	if (c_posY - 1 == 1 )
		return;
	c_posY--;
}

void CShip::moveDown()
{
	if (c_posY + 2 == 44 )
		return;
	c_posY ++;
}

bool CShip::isCollision()const
{
	return false;
}

