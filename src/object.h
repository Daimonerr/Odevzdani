#ifndef OBJECT_H
#define OBJECT_H

#include <ncurses.h>
#include <vector>
#include "timer.h"
#include "yxpart.h"
using namespace std;

/*!
* Parental class representing core of every moving object
*/
class CObject {
	public:

		/*!
		* Constructor sets core of object
		*/
		CObject(const int & y, 
				const int & x, 
				const char & coreC);

		/*!
		* Virtual destructor
		*/
		virtual ~CObject(){};

		/*!
		* Abstract for deciding if object can move in its direction
		* @return True if object cant move further
		*/
		virtual bool isCollision()const =0;

		/*!
		* Moves with object in its direction
		* @return True if move was successful
		*/
		virtual bool moveO();

		/*!
		* Move with object in its direction dependable on time
		* @param cntTime object that represents time
		* @return True if move was successful
		*/
		virtual bool moveO(CTimer & cntTime);

		/*!
		* Inserts struct that contains information about part of object into vector 
		* @param y Y offset from core
		* @param x X offset from core
		* @param oChar char that visually represents part of object
		*/
		void buildOffset(const int & y, 
						 const int & x, 
						 const char & oChar);

		/*!
		* Prints object in window based on its core positions
		*/
		void printO()const;

		/*!
		* Clears object in window based on its core positions
		*/		
		void clearO()const;

		/*!
		* Gives all collision points of object 
		* @return vector of struct that contains positions of each collision point of object (core included)
		*/
		vector<YXPART> giveCollisionPoints();

		/*!
		* Gives positions of core
		* @return struct that contains posY and posX of core
		*/
		YXPART giveCorePoint();

	protected:

		//! represents Y position of core
		int c_posY;
		
		//! represents X position of core
		int c_posX;
		
		//! represents visual view of core
		int c_coreChar;
		
		//! vector of structs that represent whole object based on core
		vector<YXPART> offset;
		
		//! number of parts that are in offset vector
		int c_offsLen;
};

#endif