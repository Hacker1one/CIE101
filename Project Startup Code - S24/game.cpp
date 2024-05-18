#include "game.h"
#include "gameConfig.h"
#include <iostream>
#include <sstream>
#include "CMUgraphicsLib\auxil.h"	// where Pause is found
#include<algorithm>
#include <memory>
#include<ctime>




game::game()
{
	step = 0;
	//Create the main window
	createWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//Create and draw the toolbar
	createToolBar();

	//Create and draw the grid
	
	

	//Create and clear the status bar
	clearStatusBar();

	checktoload();

	createGrid();
	shapesGrid->draw();	//draw the grid and all shapes it contains.
	
}

game::~game()
{
	delete pWind;
	delete shapesGrid;
}


//////////////////////////////////////////////////////////////////////////////////////////
void game::createWind(int w, int h, int x, int y) 
{
	pWind = new window(w, h, x, y);
	pWind->SetBrush(config.bkGrndColor);
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->DrawRectangle(0, 0, w, h);
}
//////////////////////////////////////////////////////////////////////////////////////////
void game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the mode
void game::createToolBar()
{
	gameToolbar = new toolbar(this);
}

void game::createGrid()
{	
	//calc some grid parameters
	point gridUpperLeftPoint = { 0, config.toolBarHeight };
	int gridHeight = config.windHeight - config.toolBarHeight - config.statusBarHeight;
	//create the grid
	shapesGrid = new grid(gridUpperLeftPoint, config.windWidth, gridHeight, this);
	shapesGrid->randomShapeGeneration();
}

void game::checktoload()
{
		bool bQuit = false;
		keytype ktInput;
		clicktype ctInput;
		char cKeyData;

		// Display initial message
		printMessage("Do you want to load a previous file. Click (y) for Yes and (n) for No");

		// Flush out the input queues before beginning
		pWind->FlushMouseQueue();
		pWind->FlushKeyQueue();

		do
		{
			pWind->SetPen(BLACK);

			ktInput = pWind->GetKeyPress(cKeyData);

			if (cKeyData == 121 || cKeyData == 89 ) {
				ostringstream output;
				output << "You chose to load ";
				pWind->DrawString(5, 180, output.str()); // Adjust Y coordinate for clarity4
				operation* op = new operLoad(this);
				bQuit = true;
			}
			else if (cKeyData == 79 || cKeyData == 110)
			{
				slevel();
				bQuit = true;
			}

			// Pause for half a second
			Pause(500);


		} while (bQuit != true);
		givesteps();
}
void game::slevel()
{
	bool bQuit = false;
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	// Display initial message
	printMessage("Select a level from 1 to 10 (Press T or t for 10)");

	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();

	do
	{
		pWind->SetPen(BLACK);

		ktInput = pWind->GetKeyPress(cKeyData);

		if ((cKeyData>=48 && cKeyData < 58) || cKeyData == 84 || cKeyData == 116) {
			if (cKeyData >= 48 && cKeyData < 58)
			{
				ostringstream output;
				output << "You chose level '" << cKeyData << "'";
				pWind->DrawString(5, 180, output.str()); // Adjust Y coordinate for clarity4
				gameToolbar->setlevel(cKeyData - 48);
				bQuit = true;
			}
			else
			{
				ostringstream output;
				output << "You chose level '10'";
				pWind->DrawString(5, 180, output.str()); // Adjust Y coordinate for clarity4
				gameToolbar->setlevel(10);
				bQuit = true;
			}
		}

		// Pause for half a second
		Pause(500);


	} while (bQuit != true); 
	givesteps();
}

void game::givesteps()
{
	int totalcompositeshapes = 0;
	for (int i = gameToolbar->getlevel(); i < 11; i++)
	{
		totalcompositeshapes += (2 * i - 1);
	}
	givens = 30 * totalcompositeshapes;
	drawgivensteps();
}

int game::getgivensteps() const
{
	return givens;
}

void game::drawgivensteps() const
{
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(1250, config.windHeight - (int)(1 * config.statusBarHeight), config.windWidth, 621);

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(1270, config.windHeight - (int)(0.85 * config.statusBarHeight), "Given Steps = ");
	pWind->DrawInteger(1410, config.windHeight - (int)(0.85 * config.statusBarHeight), givens);
}

void game::countsteps()
{
	try {}
	catch(string s)
	{}
}
void game::incrementsteps()
{
	step += 1;
	gameToolbar->dsteps();
}

int game::getsteps() const
{
	return step;
}

operation* game::createRequiredOperation(toolbarItem clickedItem)
{
	operation* op=nullptr;
	switch (clickedItem)
	{

	case ITM_SIGN:
		op = new operAddSign(this);
		printMessage("you clicked on sign");
		operations.push_back(op);
		break;
	case ITM_BALL:
		op = new operAddstandingball(this);
		printMessage("you clicked on Standing ball");
		operations.push_back(op);
		break;
	case ITM_MAN:
		op = new operAddstrawman(this);
		printMessage("you clicked on Straw Man");
		operations.push_back(op);
		break;
	case ITM_PTR:
		op = new operAddpointer(this);
		printMessage("you clicked on Pointer Towards a Ball");
		operations.push_back(op);
		break;
	case ITM_GUN:
		op = new operAddgun(this);
		printMessage("you clicked on Gun");
		operations.push_back(op);
		break;
	case ITM_HOUSE:
		op = new operAddhouse(this);
		printMessage("you clicked on House");
		operations.push_back(op);
		break;
	case ITM_BAL:
		op = new operAddbalance(this);
		printMessage("you clicked on Balance");
		operations.push_back(op);
		break;
	case ITM_INC:
		op = new operResizeUp(this);
		incrementsteps();
		printMessage("you clicked on Resize Up");
		operations.push_back(op);
		break;
	case ITM_DEC:
		op = new operResizeDown(this);
		incrementsteps();
		printMessage("you clicked on Resize Down");
		operations.push_back(op);
		break;
	case ITM_DEL:
		op = new operDelete(this);
		printMessage("you clicked on Delete");
		operations.push_back(op);
		break;
	case ITM_ROT:
		op = new operRotate(this);
		incrementsteps();
		printMessage("you clicked on Rotate");
		operations.push_back(op);
		break;
	case ITM_FLP:
		op = new operFlip(this);
		incrementsteps();
		printMessage("you clicked on Flip");
		break;
	case ITM_LVL:
		op = new operslevel(this);
		printMessage("Select a level from 1 to 10");
		operations.push_back(op);
		break;
	case ITM_REF:
		op = new operrefresh(this);
		printMessage("You clicked on Refresh");
		operations.push_back(op);
		break;
	case ITM_EXIT:
		op = new operexit(this);
		printMessage("You clicked on Exit");
		//operations.push_back(op);
		delete op;
		break;
	case ITM_HINT:
		op = new operHint(this);
		printMessage("You selected on Hint");
		operations.push_back(op);
		break;
	case ITM_SAVE:
		op = new operSave(this);
		printMessage("you clicked on Save");
		break;
	case ITM_LOAD:
		op = new operLoad(this);
		printMessage("you clicked on Load");
		break;
	}
	return op;
}




//////////////////////////////////////////////////////////////////////////////////////////

void game::printMessage(string msg) const	//Prints a message on status bar
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);
	drawgivensteps();
}


window* game::getWind() const		//returns a pointer to the graphics window
{
	return pWind;
}


string game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

grid* game::getGrid() const
{
	// TODO: Add your implementation code here.
	return shapesGrid;
}
toolbar* game::getToolbar() const
{
	return gameToolbar;
}


////////////////////////////////////////////////////////////////////////
void game::run()
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	bool isExit = false;

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - SHAPE HUNT (CIE 101 / CIE202 - project) - - - - - - - - - -");
	toolbarItem clickedItem = ITM_CNT;

	double timer = clock();
	int cnt = 0;
	do
	{
		//printMessage("Ready...");
		//1- Get user click 

		if (clock() - timer > 1000) {

			timer = clock();
			cnt++;
			gameToolbar->settime(cnt);
			gameToolbar->IncreaseTime(); // increase time by 1 second

		}
		//printMessage("Ready...");
		//1- Get user click
		pWind->GetMouseClick(x, y);	//Get the coordinates of the user click

		//2-Explain the user click
		//If user clicks on the Toolbar, ask toolbar which item is clicked
		if (y >= 0 && y < config.toolBarHeight)
		{
			clickedItem = gameToolbar->getItemClicked(x);

			//3-create the approp operation accordin to item clicked by the user
			operation* op = createRequiredOperation(clickedItem);
			if (op)
				op->Act();
			operations.push_back(op);


			//4-Redraw the grid after each action
			shapesGrid->draw();

		}
		kt = pWind->GetKeyPress(pressedkey);

		if (kt == ASCII) {
			printMessage("you clicked on ASCII");
			if (pressedkey == ' ') {
				printMessage("You clicked on Space");
				int score = gameToolbar->getscore();
				if (IsMatching(shapesGrid->getActiveShape())) {
					score += 2;
					printMessage("Mathcing !!");
					gameToolbar->setscore(score);
					
					shapesGrid->deleteActiveShape();
					shapesGrid->editShapeCount();

				}
				else {
					score--;
					printMessage("Wrong Mathcing !!");
					gameToolbar->setscore(score);

				
				}
			shapesGrid->draw();
			}
		}

		if (kt == ARROW) {
			printMessage("you clicked on arrow");
			operation* op2 = nullptr;
			op2 = new operMove(pressedkey, this);
			operations.push_back(op2);
			if (op2) {
				op2->Act();
				shapesGrid->draw();


			}
		}
		
        
	} while (clickedItem != ITM_EXIT);
}

	


bool game::IsMatching(shape *sh) {
	vector<shape*> V = shapesGrid->getshapeVector(); 
	
	for (unsigned int i = 0; i < V.size(); i++) {
		
		if (V[i]->getRefPoint().x == sh->getRefPoint().x && V[i]->getRefPoint().y == sh->getRefPoint().y && V[i]->getrotated() == sh->getrotated() && V[i]->getsize() == sh->getsize() && V[i]->getShapeType() == sh->getShapeType()) {
			
			
			cout << V[i]->getShapeType();
			V[i]->setcolor(LAVENDER);
			
			
			return true; 
			
			
			
		}
		
		
	}
	return false;
}

vector<operation*> game::getvectoroperations() const
{
	return operations;
}
