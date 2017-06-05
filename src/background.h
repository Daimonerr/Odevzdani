
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include "ship.h"
#include "load.h"


 /*!
 * Class representing ncurses map drawings and loading map from file
 */
class CBack {
	public:

		/*!
		* Constructor
		*/
		CBack();

		/*!
		* Draws borders of map and right bar with informations
		*/
		void drawMap()const;

		/*!
		* Draws starting screen, controlls and introduction with game, asks for map file
		* @param fileVect vector of structs that the map will be loaded to
		* @param cntFileObjs value will be set to total count of obstacles per map
		* @param end time when game will end
		*/
		void startMenu(vector<LOAD> & fileVect, 
					   int & cntFileObjs,
					   int & end);

		/*!
		* Prints utilities to the right bar
		* @param score players score
		* @param remainObst remaining obstacles
		* @param health current ships health
		* @param timer object that represents time
		* @param isReloading status of reloading
		* @param mag currently bullets in mag
		* @param bonus each number represents different bonus
		*/
		void printUtilities(const int & score, 
							const int & remainObst, 
							const int & health,
							CTimer & timer, 
							const bool & isReloading, 
							const int & mag, 
							const int & bonus);

		/*!
		* Prints ending screen and writes score to the file
		* @param score score at the end of the game
		*/
		void gameEnding(const int & score);

		/*!
		* Pauses the game
		*/
		void pauseGame();

		/*!
		* Loads data to vector of structs from file
		* @param fileVect vector of structs that contains set of map
		* @param cntFileObjs total count of obstacles per map
		* @param end time when game will end
		* @return True when successfuly loaded file
		*/
		bool getFile(vector<LOAD> & fileVect, 
					 int & cntFileObjs,
					 int & end);

		/*!
		* Draws tetragon
		* @param height height of tetragon
		* @param width width of tetragon
		* @param startY starting Y position of tetragon
		* @param startX starting X position of tetragon
		* @param printChar char that tetragon will be made of
		*/
		void drawSquare(const int & height, 
						const int & width, 
						const int & startY, 
						const int & startX, 
						const char & printChar)const;
		
	private:

		//! nickname of player
		char c_nickname[20];

		//! name of file that contains formated data for map
		char c_mapName[36];
};

#endif
