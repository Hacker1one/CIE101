#include "toolbar.h"
#include "game.h"
//#include "grid.h"


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(game* pG)
{	
	height = config.toolBarHeight;
	width = config.windWidth;
	score = 0;
	level = 1;
	num_lives = 5;
	this->pGame = pG;
	window* pWind = pGame->getWind();
	
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each toolbar item
	toolbarItemImages[ITM_SIGN] = "images\\toolbarItems\\toolbar_sign.jpg";
	toolbarItemImages[ITM_CAR] = "images\\toolbarItems\\car.jpg";
	toolbarItemImages[ITM_EXIT] = "images\\toolbarItems\\toolbar_Exit.jpg";
	toolbarItemImages[ITM_HOUSE] = "images\\toolbarItems\\house.jpg";
	toolbarItemImages[ITM_ICE] = "images\\toolbarItems\\ice.jpg";
	toolbarItemImages[ITM_TREE] = "images\\toolbarItems\\tree.jpg";
	toolbarItemImages[ITM_HINT] = "images\\toolbarItems\\hint.jpg";
	toolbarItemImages[ITM_DEL] = "images\\toolbarItems\\del.jpg";
	toolbarItemImages[ITM_ROT] = "images\\toolbarItems\\rot.jpg";
	
	

	
	
	
	
	string heart = "images\\toolbarItems\\Heartt.jpg";

	//TODO: Prepare image for each toolbar item and add it to the list

	//Draw toolbar item one image at a time
	for (int i = 0; i < ITM_CNT; i++)
		pWind->DrawImage(toolbarItemImages[i], i * config.toolbarItemWidth, 0, config.toolbarItemWidth, height);
	
	//Draw the lives
	for (int i = config.hearts_beg_pos_factor; i < (config.hearts_beg_pos_factor+ num_lives) ; i++)    
	pWind->DrawImage(heart, i * config.hearts_width, 0, config.hearts_width, config.hearts_height);

	//Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, height,width , height);

	// Draw the score
	pWind->SetPen(config.TextColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.XscorePosition, config.YscorePosition,"Score = ");
	pWind->DrawInteger(config.XscorePosition+config.ScoreLength, config.YscorePosition, score);


	// Draw the Level
	pWind->SetPen(config.TextColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.XlevelPosition, config.YlevelPosition, "Level = ");
	pWind->DrawInteger(config.XlevelPosition + config.LevelLength, config.YlevelPosition, level);


}



//handles clicks on toolbar icons, returns ITM_CNT if the click is not inside the toolbar
toolbarItem toolbar::getItemClicked(int x)
{
	
	if (x > ITM_CNT * config.toolbarItemWidth)	//click outside toolbar boundaries
		return ITM_CNT;
	
	
	//Check whick toolbar item was clicked
	//==> This assumes that toolbar items are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

	return (toolbarItem)(x / config.toolbarItemWidth);

}

void FlipCircle(window* wind, circle* c) {
	
}