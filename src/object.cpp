#include "object.h"


CObject::CObject(const int & y, const int & x, const char & coreC): c_posY(y),c_posX(x),c_coreChar(coreC), c_offsLen(0)
{}


vector<YXPART> CObject::giveCollisionPoints()
{
	//! first push_back core itself
	vector<YXPART> tmp;
	YXPART core(c_posY,c_posX, c_coreChar);
	tmp.push_back(core);
	
	//! then push_back others parts by adding offsets to core positions
	for (int i = 0; i < c_offsLen; i++)
	{
		YXPART add(offset[i].offsY+c_posY,offset[i].offsX+c_posX, 'X');
		tmp.push_back(add);
	}
	
	return tmp;
}

YXPART CObject::giveCorePoint()
{
	YXPART tmp(c_posY,c_posX, c_coreChar);
	return tmp;
}

void CObject::buildOffset(const int & y,const int & x,const char & oChar)
{
	YXPART tmp(y,x,oChar);
	offset.push_back(tmp);
	c_offsLen++;
}

void CObject::printO()const
{
	mvaddch(c_posY, c_posX, c_coreChar);
	for (int i = 0; i < c_offsLen; i++){
		mvaddch(c_posY + offset[i].offsY, c_posX + offset[i].offsX, offset[i].offsChar);
	}
}

void CObject::clearO()const
{
	mvaddch(c_posY, c_posX, ' ');
	for (int i = 0; i < c_offsLen; i++){
		mvaddch(c_posY + offset[i].offsY, c_posX + offset[i].offsX, ' ');
	}
}


bool CObject::moveO()
{
	return true;
}

bool CObject::moveO(CTimer & cntTime)
{
	return true;
}