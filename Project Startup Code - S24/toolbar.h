#pragma once
#include "gameConfig.h"
////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class game;
class toolbar
{

private:
	int height, width,level,num_lives,score;	
	string toolbarItemImages[ITM_CNT]; //array to hold paths to images of diffrent items in the toolbar
	game* pGame;

public:
	toolbar(game* r_pGame);
	toolbarItem getItemClicked(int x);	//handles clicks on toolbar icons, returns the "enum" of the clicekd item
	void setlevel(int );
	void dscorelevel();
	void drawlives();
	void dsteps();
	void decrementlives();
	void setscore(int);
	void setlives(int);
	int getlevel() const;
	int getscore() const;
	int getlives() const;
};

