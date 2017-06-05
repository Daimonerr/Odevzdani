#ifndef GAME_H
#define GAME_H

#include <time.h>
#include "background.h"


#define BONUSAMMO 1
#define BONUSINDESTRUCT 2
#define BONUSGUNS 3

 /*!
 * Class representing a game, every important variable is stored in this class
 * and it is controlling whole flow of the game, moving objects, accepting output keys
 * and checking/deleting collided object
 */

class CGame {
	public:

		/*!
		* Constructor initializes variables and ncurses screen
		*/
		CGame();

		/*!
		* Implicit destructor frees every not freed allocations and closes ncurses
		*/
		~CGame();

		/*!
		* Starts the game, initializes game environment, contains game cycle, calls other classes and methods 
		* to load/check/move/destroy objects and interactive menus
		*/
		void runGame();
		
		/*!
		* Spawn flying obstacles dependable on theirs spawntime and type
		*/
		void spawnObstacles();
	
		/*!
		* Indicates end of the game after level or if health reaches zero points
		* @return True if health is 0 or playtime=c_end time 
		*/
		bool gameOver();
		
		/*!
		* Move with all shot bullets if its possible, else destroys them
		*/
		void moveBullets();

		/*!
		* Move with all spawned obstacles if its possible, else destroys them
		*/
		void moveObstacles();

		/*!
		* Decides what to do with pressed key (move ship, fire, pause, reload)
		*/
		void gameControll();

		/*!
		* Starts reloading ammo in mag (4 secs), sets c_isReloading on true
		*/
		void reloadMag();

		/*!
		* Randomly actives one of 3 available bonuses (indestructability, unlimited ammo, additional guns)
		*/
		void rollBonus();
		

		/*!
		* Controlls collisions between ship and obstacles (ship with every obstacle)
		*/
		void checkShip();

		/*!
		* Controlls collisions between bullets and obstacles (every bullet with every obstacle)
		*/
		void checkBullets();

		/*!
		* Reloads mag 4 seconds after calling "reloadMag", controlls reload time
		*/
		void checkReloading();

		/*!
		* Turns off random bonus 10 seconds after calling "rollBonus", switches c_bonus to 0
		*/
		void checkBonuses();

		/*!
		* Compares positions of bullet and all spawned obstacles, if true destroys bullet and obstacle
		* @param bullet struct carrying Y and X positions of bullet
		* @param index represents position of inserted bullet in vector
		* @return True when bullet hits obstacle
		*/
		bool hitBullet(YXPART & bullet, 
					   const int & index);

		/*!
		* Compares positions of inserted ship collision point and all spawned obstacles
		* if true lowers health and destroys obstacle
		* @param shipCPoint collision point of ship
		* @return True when collision point of ship hits obstacle
		*/
		bool hitShip(YXPART & shipCPoint);

		/*!
		* Pop_backs requested obstacle from vector, frees allocated memory
		* @param obstIndex index representing position of obstacle in vector
		*/
		void deleteObst(const int & obstIndex);

		/*!
		* Pop_backs requested bullet from vector
		* @param bulletIndex index representing position of bullet in vector
		*/
		void deleteBullet(const int & bulletIndex);
		
	private:
		
		//! vector of pointers to allocated obstacles, stores obstacleA,obstacleB,obstacleC
		vector<CObstacle*> obstacles;

		//! vector of currently active bullets
		vector<CBullet> ammo;
		
		//! map vector of structs that contain data about times, positions and types of obstacles
		vector<LOAD> map;
		
		//! object of class that represents time in game cycle
		CTimer timer;
		
		//! object that represents ship	
		CShip battleShip;
		
		//! object that sets background of the game (interactive menus, reads data from files, draws map and utilities)
		CBack background;			
		
		//! currently spawned obstacles
		int c_crntObst;
		
		//! total count of obsacles per map
		int c_cntFileObjs;
		
		//! players score
		int c_score;
		
		//! healths of ship
		int c_health;
		
		//! remaining not yet spawned obstacles
		int c_remainObst;
		
		//! bullets in mag
		int c_mag;
		
		//! represents bonus (0 = not active)
		int c_bonus;
		
		//! time of bonus end (when playtime reaches this time, then bonus will end)
		int c_bonusTime;
		
		//! count of currently existing bulets
		int c_cntBullets;
		
		//! time of reload (when playtime reaches this time, then gun will reload)
		int c_reloadT;
		
		//! indicates if ship is currently reloading
		bool c_isReloading;
		
		//! end of the game (when playtime reaches this time, then game will end)
		int c_end;		
};

#endif