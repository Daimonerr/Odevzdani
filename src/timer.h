#ifndef TIMER_H
#define TIMER_H

#include <string>
using namespace std;

/*!
* Class representing time in game
*/
class CTimer {
	public:

		/*!
		* Constructor
		*/
		CTimer();

		/*!
		* Increases 0,02 seconds to game time
		*/
		void addTime();

		/*!
		* Makes string from c_min and c_sec
		* @return String of time in format X:XX
		*/
		string printTime();

		/*!
		* Gives milliseconds of current time
		* @return c_msec
		*/
		int getMsec();

		/*!
		* Gives current playtime
		* @return playtime in seconds
		*/
		int getPlaytime();

		/*!
		* Gives seconds increased by plusT
		* @param plusT time in seconds
		* @return current time + plusT in seconds
		*/
		int endTime(const int & plusT);

	private:

		//! representing minutes
		int c_min;
		
		//! representing seconds
		int c_sec;
		
		//! representing miliseconds
		int c_msec;
};

#endif
