#include "game.h"

CGame::CGame(): c_crntObst(0), c_cntFileObjs(0),  c_score(0), 
				c_health(3), c_remainObst(0), c_mag(10),
				c_bonus(0), c_bonusTime(0), c_cntBullets(0), 
				c_reloadT(0), c_isReloading(false), c_end(0)
{
	initscr();	
	srand(time(NULL));
}


CGame::~CGame()
{
	nodelay(stdscr, false);

	/*!
	* Deletes every not freed object from vector
	*/
	for (auto it = 	obstacles.begin() ; it != obstacles.end(); ++it){ 
		delete (*it);}
    obstacles.clear();
    ammo.clear();
    map.clear();
	nodelay(stdscr,false);
	keypad(stdscr, false);
	endwin();
}

void CGame::runGame()
{
	/*!
	* Calls class background to load obstacles to vector of structs
	* that represent obstacles, initialize interactive menu
	*/	
	background.startMenu(map, c_cntFileObjs, c_end);
	c_remainObst = c_cntFileObjs;
	background.drawMap();


	noecho();
	curs_set(0);
	nodelay(stdscr,true);
	keypad(stdscr, true);
	

	while( ! gameOver() )
	{

		battleShip.printO();
		spawnObstacles();

		moveBullets();
		moveObstacles();
		
		refresh();
		checkShip();
		checkBullets();
		checkBonuses();

		usleep(20000);
		battleShip.clearO();
		checkReloading();
		gameControll();
		background.printUtilities(c_score, c_remainObst, c_health, timer, c_isReloading, c_mag, c_bonus);
		
		//! adds 0,02 sec to "gametime", that represents timer
		timer.addTime();
	}

	background.gameEnding(c_score);
}

void CGame::spawnObstacles()
{
	for (int i = 0; i < c_cntFileObjs; i++)
	{
		//! spawn obstacle when its spawntime is equal to playtime, allocates new obstacle and push_back it to vector
		if ( map[i].time == timer.getPlaytime() && timer.getMsec() == 0 )
		{
			switch (map[i].type)
			{
				case 'A':
					obstacles.push_back(new CObstacleA(map[i].y,map[i].x, '#',map[i].sp));
					break;

				case 'B':
					obstacles.push_back(new CObstacleB(map[i].y,map[i].x, '#',map[i].sp));			
					break;

				case 'C':
					obstacles.push_back(new CObstacleC(map[i].y,map[i].x, '#',map[i].sp));			
					break;
			}

			c_crntObst++;
			c_remainObst--;
		}
	}
}

bool CGame::gameOver()
{
	if ( c_health == 0 || timer.getPlaytime() == c_end)
		return true;

	return false;
}


void CGame::moveBullets()
{
	for (int i = 0; i < c_cntBullets; i++)
	{
		//! if bullet is flying out of map it will destroy it 
		if ( ! ammo[i].moveO())
		{
			deleteBullet(i);
			i--;
		}
	}	
}

void CGame::moveObstacles()
{
	for (int i = 0; i < c_crntObst; i++)
	{
		//! calls move on every obstacle, if its unable to move further it will destroy
		if( ! obstacles[i]->moveO(timer)){
			deleteObst(i);
			i--;
		}
	}
}

void CGame::gameControll()
{
	//! scans pressed key on its meaning decides what to do
	switch (getch())
	{
		case KEY_UP:
			battleShip.moveUp();
			break;

		case KEY_DOWN:
			battleShip.moveDown();
			break;

		case KEY_LEFT:
			battleShip.moveLeft();
			break;

		case KEY_RIGHT:
			battleShip.moveRight();
			break;
		
		case 'f':
			if (c_isReloading==true)
				break;
			if (c_mag != 0)
			{
				ammo.push_back(battleShip.newBullet());
				c_cntBullets++;

				//! if bonus additional guns is active, it shoots from 2 more places for cost of 1 bullet
				if (c_bonus == BONUSGUNS){
					ammo.push_back(battleShip.newBullet(0,-3));
					ammo.push_back(battleShip.newBullet(0,3));
					c_cntBullets += 2;
				}
				//! if bonus ammo is active, firing doesnt cost anything
				if(c_bonus != BONUSAMMO)
					c_mag--;
			}
			break;
		case 'g':
			background.pauseGame();
			break;

		case 'r':
			if (c_isReloading != true)
				reloadMag();
	}
}


void CGame::reloadMag()
{
	c_isReloading = true;
	c_reloadT = timer.endTime(4);
}

void CGame::rollBonus()
{
	//! generates random number from 1-3
	int rndNumber = rand() % 3 + 1;
	c_bonus = rndNumber;
	//! sets bonus time to 10 seconds
	c_bonusTime = timer.endTime(10);
}


void CGame::checkShip()
{
	//! create new vector that contains collision points of ship
	vector<YXPART> shipCPoints(battleShip.giveCollisionPoints());

	for ( int i = 0; i < 21; i++)
	{
		if (hitShip(shipCPoints[i]))
			return;
	}
}

void CGame::checkBullets()
{
	for ( int i = 0; i < c_cntBullets; i++)
	{
		//! gives position of bullets Y and X pos and then compare it
		YXPART bullet(ammo[i].giveCorePoint());
		if( hitBullet(bullet, i))
			return;
	}	
}

void CGame::checkReloading()
{
	if (c_isReloading == true && c_reloadT == timer.getPlaytime())
	{
		c_mag = 10;
		c_isReloading = false;
	}
}

void CGame::checkBonuses()
{
	//! every 500 points of score it turns on random bonus
	if (c_score % 500 == 0 && c_bonus==0 && c_score != 0)
		rollBonus();
	//! turn off bonus when end of bonus time equals to playtime
	if(c_bonusTime == timer.getPlaytime())
	{
		c_bonusTime=0;
		c_bonus=0;
	}
}


bool CGame::hitBullet(YXPART & bullet, const int & index)
{
	for( int j = 0; j < c_crntObst; j++)
	{
		//! compares all obstacles with inserted Y and X position, if its the same it destroys bullet and obstacle
		if (obstacles[j]->collide(bullet.offsY,bullet.offsX))
		{	
			deleteBullet(index);
			deleteObst(j);
			c_score += 20;
			return true;
		}
	}
	return false;
}

bool CGame::hitShip(YXPART & shipCPoint)
{
	for( int j = 0; j < c_crntObst; j++)
	{
		//! compares every obstacle if it hase the same position as inserter collision point
		if (obstacles[j]->collide(shipCPoint.offsY,shipCPoint.offsX))
		{
			deleteObst(j);
			//! when bonus indestructibility is active it doesnt harm the ship
			if(c_bonus == BONUSINDESTRUCT )
				c_score += 20;
			else
				c_health--;
			return true;
		}
	}
	return false;
}

void CGame::deleteObst(const int & obstIndex)
{
	auto it = (obstacles.begin()+obstIndex);
	delete (*it);
	obstacles.erase(obstacles.begin()+obstIndex);
	c_crntObst--;
}

void CGame::deleteBullet(const int & bulletIndex)
{
	ammo.erase(ammo.begin()+bulletIndex);
	c_cntBullets--;
}
