#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include "gameConfig.h"
#include "fstream"
#include <iostream>
#include <vector>
#include "random"
#include "cmath"
#include "sstream"

using namespace std;

/////////////////////////////////// class operation  //////////////////
operation::operation(game* r_pGame)
{
	pGame = r_pGame;
}


/////////////////////////////////// class operAddSign  //////////////////

operAddSign::operAddSign(game* r_pGame):operation(r_pGame)
{
}
void operAddSign::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Sign(pGame, signShapeRef , RED);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);




	
}



operAddgun::operAddgun(game* r_pGame) :operation(r_pGame)
{
}
void operAddgun::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point signShapeRef = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new Gun(pGame, signShapeRef,RED);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);

}





operAddstandingball::operAddstandingball(game* r_pGame) :operation(r_pGame)
{
}
void operAddstandingball::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point blusblock = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new standingball(pGame,blusblock , RED);

	////Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);





}




operAddstrawman::operAddstrawman(game* r_pGame) :operation(r_pGame)
{
}
void operAddstrawman::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point blusblock = { xGrid,yGrid };


	shape* psh = new strawman(pGame, blusblock , RED);

	//Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);





}



operAddpointer::operAddpointer(game* r_pGame) :operation(r_pGame)
{
}
void operAddpointer::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point blusblock = { xGrid,yGrid };



	//create a sign shape
	shape* psh = new pointerToAball(pGame, blusblock , RED);

	////Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);





}

operAddhouse::operAddhouse(game* r_pGame) :operation(r_pGame)
{
}
void operAddhouse::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point blusblock = { xGrid,yGrid };

	//create a sign shape
	shape* psh = new house(pGame, blusblock , RED);

	////Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);





}


operAddbalance::operAddbalance(game* r_pGame) :operation(r_pGame)
{
}
void operAddbalance::Act()
{
	window* pw = pGame->getWind();

	//TODO:
	// Don't allow adding new shape if there is alreday an active shape

	//align reference point to the nearest grid point
	int xGrid = config.RefX - config.RefX % config.gridSpacing;
	int yGrid = config.RefY - config.RefX % config.gridSpacing;

	//take the aligned point as the sign shape ref point
	point blusblock = { xGrid,yGrid };
	
	//create a sign shape
	shape* psh = new balance(pGame, blusblock , RED);

	////Add the shape to the grid
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);





}





operFlip::operFlip(game* r_pGame) :operation(r_pGame)
{
}
void operFlip::Act()
{
	
	shape* psh = pGame->getGrid()->getActiveShape();
	psh->Flip();
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}
operRotate::operRotate(game* r_pGame) :operation(r_pGame)
{
}
void operRotate::Act()
{

	shape* psh = pGame->getGrid()->getActiveShape();
	psh->Rotate();
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}



operMove::operMove(char k , game* r_pGame) :operation(r_pGame)
{
	key=k;
}
void operMove::Act() {
	shape* psh = pGame->getGrid()->getActiveShape();
	psh->move(key);
	pGame->incrementsteps();
	grid* pGrid = pGame->getGrid();
	pGrid->setActiveShape(psh);
}

operDelete::operDelete(game* r_pGame) :operation(r_pGame)
{
}
void operDelete::Act()
{
	window* pw = pGame->getWind();
	grid* pgrid = pGame->getGrid();
	
	pgrid->deleteActiveShape();
	pgrid->editShapeCount();
}



operResizeUp::operResizeUp(game* r_pGame) :operation(r_pGame)
{
}

void operResizeUp::Act()
{
	window* pw = pGame->getWind();
	grid* pgrid = pGame->getGrid();
	shape* shp = pgrid->getActiveShape();
	if(shp!=nullptr)
	shp->resizeUp();
}

operResizeDown::operResizeDown(game* r_pGame) :operation(r_pGame)
{
}

void operResizeDown::Act()
{
	window* pw = pGame->getWind();
	grid* pgrid = pGame->getGrid();
	shape* shp = pgrid->getActiveShape();
	if (shp != nullptr)
	shp->resizeDown();
}

operslevel::operslevel(game* r_pGame) : operation(r_pGame)
{
}
void operslevel::Act()
{
	window* pw = pGame->getWind();
	pGame->slevel();
}

operexit::operexit(game* r_pGame) : operation(r_pGame)
{
}

void operexit::Act()
{
	
	window* pw = pGame->getWind();
	grid* pgrid = pGame->getGrid();
	vector<operation*> oper = pGame->getvectoroperations();
	vector<shape*>V = pgrid->getshapeVector();
	toolbar* tb = pGame->getToolbar();
	for (int i = 0; i < V.size(); i++)
	{
		delete V[i];
		V[i] = nullptr;
	}
	pGame->getToolbar()->decrementlives();
	if (pgrid->getActiveShape() != nullptr)
	{
		delete pgrid->getActiveShape();
	}
	
	delete tb;
	tb = nullptr;
	
	for (int i = 0; i < oper.size(); i++)
	{
		delete oper[i];
		oper[i] = nullptr;
	}
	delete pGame;
}

operHint::operHint(game* r_pGame) : operation(r_pGame)
{
}

void operHint::Act() {
	int i = 0;
	grid* pgrid = pGame->getGrid();
	vector <shape*> v  = pgrid->getshapeVector();
	random_device randshape;
	uniform_int_distribution<int> rrandshape(0,4);
	i = rrandshape(randshape);
	v[i]->setcolor(GREEN);
}

operrefresh::operrefresh(game* r_pGame) : operation(r_pGame)
{
}

void operrefresh::Act()
{

	int totalcompositeshapes = 2* pGame->getToolbar()->getlevel() -1;
	grid* pgrid = pGame->getGrid();
	vector<shape*>V = pgrid->getshapeVector();
	toolbar* tb = pGame->getToolbar();
	if (tb->getlives() > 1)
	{
		for (int i = 0; i < totalcompositeshapes; i++)
		{
			delete V[i];
			V[i] = nullptr;
		}
		pGame->getToolbar()->decrementlives();
		if (pgrid->getActiveShape() != nullptr)
		{
			delete pgrid->getActiveShape();
		}
		delete pgrid;
		pgrid = nullptr;

		pGame->createGrid();
	}
	else
	{
		pGame->printMessage("It is your last life. You no longer can use refresh");
	}
}


operSave::operSave(game* r_pGame) : operation(r_pGame)
{
}
void operSave::Act()
{
	int lev = pGame->getToolbar()->getlevel();
	int life = pGame->getToolbar()->getlives();
	int scre = pGame->getToolbar()->getscore();
	ofstream outfile;
	outfile.open("progress.txt");
	outfile << scre << "\n" << lev << "\n" << life << "\n";
	pGame->getGrid()->SaveShapes(outfile);
	outfile.close();
}
operLoad::operLoad(game* r_pGame) : operation(r_pGame)
{
}
void operLoad::Act()
{
	ifstream infile;
	infile.open("progress.txt");
	if (infile) {
		int lev, life, scre;
		infile >> scre >> lev >> life;
		pGame->getToolbar()->setscore(scre);
		pGame->getToolbar()->setlevel(lev);
		pGame->getToolbar()->setlives(life);
		pGame->getGrid()->LoadShapes(infile);
		infile.close();
	}
	else
		pGame->printMessage("No saved progress");
}


