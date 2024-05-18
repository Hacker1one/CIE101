#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "toolbar.h"
#include "operations.h"
#include "grid.h"



//Main class that coordinates the game operation
class game
{

	/// Add more members if needed

	toolbar* gameToolbar;
	keytype kt;
	window* pWind;	//Pointer to the CMU graphics window
	grid* shapesGrid;
	char pressedkey;
	vector<operation*>operations;
	int step;
	long int givens = 0;

public:
	game();
	~game();

	string getSrting() const;	 //Returns a string entered by the user
	void createWind(int, int, int, int); //creates the game window
	void clearStatusBar() const;	//Clears the status bar
	void printMessage(string msg) const;	//Print a message on Status bar
	void createToolBar();		//creates the toolbar
	void createGrid();		//creates the shapes grid
	
	void slevel();
	void countsteps();
	void incrementsteps();
	int getsteps() const;
	void givesteps();
	void drawgivensteps()const;

	int getgivensteps() const;
	vector<operation*> getvectoroperations() const;
	window* getWind() const;		//returns a pointer to the graphics window
	grid* getGrid() const;		//returns a pointer to the shapes grid
	toolbar* getToolbar() const;
	bool IsMatching(shape*);
	void checktoload();
	//creates an operation according to the toolbar item clicked
	operation* createRequiredOperation(toolbarItem clickedItem);
	


	void run();	//start the game

};

