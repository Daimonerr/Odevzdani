#ifndef YXPART_H
#define YXPART_H

/*!
* Struct representing part/offset of object (can be used for both)
*/
class YXPART {
	public:

		/*!
		* Constructor
		* @param y Y position/offset of part
		* @param x X position/offset of part
		* @param c char representing part
		*/
		YXPART(const int & y, 
			   const int & x, 
			   const char & c);
		
		//! offset Y from core  
		int offsY;

		//! offset X from core
		int offsX;
		
		//! char representing part
		char offsChar;
};

#endif