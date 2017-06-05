#ifndef LOAD_H
#define LOAD_H

/*!
* Struct representing spawning information about obstacle 
*/
struct LOAD{

	/*!
	* Constructor
	* @param stX starting X position of obstacle
	* @param stTime time when the obstacle will spawn
	* @param stSpeed obstacle moving speed
	* @param typeO obstacle type
	*/
	LOAD(const int & stX, 
		 const int & stTime, 
		 const int & stSpeed, 
		 const char & typeO);
	
	//! Y starting position
	int y;

	//! X starting position
	int x;

	//! spawning time
	int time;

	//! speed
	int sp;

	//! obstacle type
	char type;
};

#endif