#include "operations.h"
#include "game.h"
#include "CompositeShapes.h"
#include "gameConfig.h"
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
	shape* psh = new Sign(pGame, signShapeRef );

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
	shape* psh = new Gun(pGame, signShapeRef);

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
	shape* psh = new standingball(pGame,blusblock);

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


	shape* psh = new strawman(pGame, blusblock);

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
	shape* psh = new pointerToAball(pGame, blusblock);

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
	//shape* psh = new house(pGame, blusblock);

	////Add the shape to the grid
	//grid* pGrid = pGame->getGrid();
	//pGrid->setActiveShape(psh);





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
	//shape* psh = new Triangle(pGame, blusblock, 40 ,50);

	////Add the shape to the grid
	//grid* pGrid = pGame->getGrid();
	//pGrid->setActiveShape(psh);





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

