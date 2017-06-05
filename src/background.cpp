#include "background.h"

CBack::CBack()
{
	c_nickname[0]='\0';
	c_mapName[0]='\0';
}

void CBack::drawMap()const
{
	drawSquare(45, 60, 0, 0, (char)219);
	drawSquare(45, 15, 0, 60, (char)219);
	
	attron(A_BOLD);
	attron(A_UNDERLINE);
	mvprintw(3,66,"TIME");
	mvprintw(7,66,"REMAIN");
	mvprintw(11,66,"SCORE");
	mvprintw(15,66,"BONUS");
	mvprintw(34,66,"MAG");
	mvprintw(38,65,"HEALTH");
	attroff(A_UNDERLINE);
	attroff(A_BOLD);
	refresh();
}


void CBack::startMenu(vector<LOAD> & fileVect, int & cntFileObjs, int & end)
{
	printw("Enter your nickname: ");
	getnstr(c_nickname, 19);
	clear();

	drawSquare(45, 60, 0, 0, (char)219);
	attron(A_BOLD);
	mvprintw(10,13,"PLEASE WRITE NAME OF THE MAP FILE");
	attroff(A_BOLD);

	attron(A_UNDERLINE);
	mvprintw(16,5,"SUMMARY:");
	attroff(A_UNDERLINE);
	mvprintw(18,10,"This game is a action-shooter.");
	mvprintw(19,10,"Your main objective is to destroy as many"); 
	mvprintw(20,10,"obstacles as u can and not being hit by them.");					
	mvprintw(21,10,"Game has 10 levels in total.");
	mvprintw(22,10,"Higher levels are going to be harder to survive.");
	mvprintw(23,10,"Each destroyed obstacle gives you +20 score.");
	mvprintw(24,10,"Every 400 points of score will give you");
	mvprintw(25,10,"random bonus (more guns, shield, extra health).");
	attron(A_UNDERLINE);
	mvprintw(27,5,"CONTROLLS:");
	attroff(A_UNDERLINE);

	mvprintw(29,10,"Right Arrow-Key - to move right");
	mvprintw(31,10,"Left Arrow-Key  - to move left");
	mvprintw(33,10,"Upper Arrow-Key - to move up");
	mvprintw(35,10,"Lower Arrow-Key - to move down");
	mvprintw(37,10,"F               - to shoot");
	mvprintw(39,10,"G               - to pause the game");
	mvprintw(39,10,"R               - to reload");
	move(11,22);

	while ( ! getFile(fileVect,cntFileObjs, end))
	{
		mvprintw(11,22,"                        ");
		mvprintw(13,17,"Invalid file. Try again.");
		move(11,22);
	}

	mvprintw(13,7,"Successfuly loaded. Press any key to continue.");
	getch();
	clear();
}

void CBack::printUtilities (const int & score, 
							const int & remainObst, 
							const int & health,
							CTimer & timer, 
							const bool & isReloading, 
							const int & mag,
							const int & bonus) 
{
	mvprintw(8,67,"   ");
	mvprintw(8,67,"%d", remainObst);
	mvprintw(12,67,"%d", score);
	mvprintw(40,67,"%d", health);
	mvprintw(4,66,"%s", timer.printTime().c_str());	

	switch(bonus)
	{
		case 0:
			mvprintw(16,65,"       ");
			break;
		case 1:
			mvprintw(16,67,"AMMO");
			break;
		case 2:
			mvprintw(16,65,"INDESTR");
			break;
		case 3:
			mvprintw(16,67,"GUNS");
			break;
	}

	if (isReloading == true)
		mvprintw(35,64,"RELOADING");
	else{
		mvprintw(35,64,"         ");
		mvprintw(35,67,"%d", mag);
	}

}

void CBack::gameEnding(const int & score)
{
	clear();
	nodelay(stdscr,false);

	//! opens file score.txt and inserts to it
	FILE *scoreFile = fopen("score.txt","a");
	fprintf(scoreFile, "Nickname: %s   Map: %s   Score: %d\n", c_nickname, c_mapName, score);
	fclose(scoreFile);

	drawSquare(45, 60, 0, 0, (char)219);
	
	attron(A_BOLD);
	mvprintw(9,18,"END OF THE GAME");
	mvprintw(10,10,"Your score was added to file score.txt");
	attroff(A_BOLD);
	getch();
}

void CBack::pauseGame()
{
	//! sets that ncurses window will wait until getch()
	nodelay(stdscr, false);
	mvprintw(34,65,"PAUSED");
	getch();
	mvprintw(34,65,"      ");
	nodelay(stdscr, true);
}

bool CBack::getFile(vector<LOAD> & fileVect, 
					int & cntFileObjs,
					int & end)
{
	//! variables that will temporarly store line from file
	int controll,x,time,speed;
	char type;

	FILE *mapFile;
	getnstr(c_mapName,19);
	cntFileObjs = 0;
	mapFile = fopen(c_mapName,"r");
	
	//! file open fails
	if (mapFile == NULL)
		return false;

	//! continuously loads lines from file, return false if it has wrong format
	while ( (controll = fscanf(mapFile, "%d %d %d %c", &x, &time, &speed, &type)) != EOF && ( type == 'A' || type == 'B' || type == 'C'))
	{
		if (controll < 3)
		{
			cntFileObjs=0;
			fclose(mapFile);
			fileVect.clear();
			return false;
		}

		LOAD tmp(x,time,speed,type);
		fileVect.push_back(tmp);
		cntFileObjs++;
	}

	//! controll if file is empty = zero objects were loaded
	if (cntFileObjs == 0)
		return false;
	//! sets end of the game 25 seconds after last obstacle is spawned
	end = fileVect[cntFileObjs-1].time + 25;
	fclose(mapFile);

	return true;
}

void CBack::drawSquare(const int & height,const int & width, const int & startY, const int & startX, const char & printChar)const
{
	attron(A_BOLD);
	for (int i = startY; i < (height+startY); i++)
	{
		mvaddch(i, startX, printChar);
		mvaddch(i, startX+width, printChar);
	}

	for (int i = startX; i < (width+startX+1); i++)
	{
		mvaddch(startY, i, printChar);
		mvaddch(startY+height, i, printChar);
	}
	attroff(A_BOLD);
}