#include "grid.h"
#include "iostream"
#include "game.h"
#include "gameConfig.h"
#include "fstream"
#include "random"
#include "cmath"
#include "sstream"

using namespace std;

grid::grid(point r_uprleft, int wdth, int hght, game* pG)
{
	uprLeft = r_uprleft;
	grid_height = hght;
	grid_width = wdth;
	pGame = pG;
	rows = grid_height / config.gridSpacing;
	cols = grid_width / config.gridSpacing;
	shapeCount = 0;
	
	/*for (int i = 0; i < MaxShapeCount; i++)
		shapeVector[i] = nullptr;*/

	activeShape = nullptr;

}

grid::~grid()
{
	for (int i = 0; i < shapeCount; i++)
		delete shapeVector[i];
}

void grid::draw() const
{
	clearGridArea();
	window* pWind = pGame->getWind();
	
	pWind->SetPen(config.gridDotsColor,1);
	pWind->SetBrush(config.gridDotsColor);

	//draw dots showing the grid reference points
	for (int r = 1; r < rows; r++)
		for (int c = 0; c < cols; c++)
			pWind->DrawCircle(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y, 1);
			//pWind->DrawPixel(c * config.gridSpacing, r * config.gridSpacing + uprLeft.y);

	//Draw ALL shapes
	for (shape* i : shapeVector)
		i->draw();
	//Draw the active shape
	if(activeShape)
		activeShape->draw();
}

void grid::clearGridArea() const
{
	window* pWind = pGame->getWind();	
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(uprLeft.x, uprLeft.y, uprLeft.x + grid_width, uprLeft.y + grid_height);
}

color grid::getcolor(int c) {
	switch (c) {
	case  0:
		return BLACK;
	case 1:
		return GREY;
	case 2:
		return YELLOW;
	case 3:
		return GREEN;
	case 4:
		return ORANGE;
	case 5:
		return RED;


	}
}

void grid::randomShapeGeneration()
{
	level=pGame->getToolbar()->getlevel();
	cout << level;
	int num_iterations = (2 * level) - 1;
	for (int i = 0; i < num_iterations; i++)
	{
		random_device randrotation;
		uniform_int_distribution<int> rrandrotation(0, 3);
		int rotationrand = rrandrotation(randrotation);


		random_device randReferenceX;
		uniform_int_distribution<int> rrandReferenceX(0, config.windWidth/2);
		int xrand = rrandReferenceX(randReferenceX);

		random_device randReferenceY;
		uniform_int_distribution<int> rrandReferenceY(1.25* config.toolBarHeight, 0.75*config.windHeight);
		int yrand = rrandReferenceY(randReferenceY);

		xrand = xrand - xrand % config.gridSpacing;
		yrand = yrand - yrand % config.gridSpacing;

		point randRef = { xrand ,yrand };
		
		random_device randsize;
		uniform_int_distribution<int> rrandsize(1, 5);
		int sizerand = rrandsize(randsize);

		random_device randcolor;
		uniform_int_distribution<int> rrandcolor(0, 5);
		int colorrand = rrandcolor(randcolor);
		
		random_device randshape;
		uniform_int_distribution<int> rrandshape(3, 9);
		int shaperand = rrandshape(randshape);

		if (level >= 3)
			colorrand = 0;

		shape* sh = nullptr;

		switch (shaperand)
		{
		case GUN:
			sh = new Gun(pGame, randRef, getcolor(colorrand));
			break;
		case POINTER:
			sh = new pointerToAball(pGame, randRef, getcolor(colorrand));
			break;
		case HOS:
			sh = new house(pGame, randRef, getcolor(colorrand));
			break;
		case MAN:
			sh = new strawman(pGame, randRef, getcolor(colorrand));
			break;
		case  STDBALL:
			sh = new standingball(pGame, randRef, getcolor(colorrand));
			break;
		case SIGN:
			sh = new Sign(pGame, randRef, getcolor(colorrand));
			break;
		case BAL:
			sh = new Sign(pGame, randRef, getcolor(colorrand));
		}
		for (int i = 0; i < rotationrand + 1; i++)
			sh->Rotate();
		base = pow(2, (sizerand - 3)) * sh->getblockbase();
		height = pow(2, (sizerand - 3)) * sh->getblockheight();





		/*switch (sizerand) {
		case 1:
			sh->resizeDown();
			sh->resizeDown();
			break;

		case 2:
			sh->resizeDown();
			break;
		case 3:
			break;
		case 4:
			sh->resizeUp();
			break;
		case 5:
			sh->resizeUp();
			sh->resizeUp();
			break;
		}*/
		sizerand = 3;
		sh->setxrange(base);
		sh->setyrange(height);
		if (!addShape(sh))
			num_iterations++;

	}


}





//Adds a shape to the randomly created shapes list.
bool grid::addShape(shape* newShape)
{

	//TODO:
	// 1- Check that the shape can be drawn witout being clipped by grid boundaries
	// 2- check shape count doesn't exceed maximum count
	// return false if any of the checks fail

	//Here we assume that the above checks are passed
	if (level <= 2) {

	}
	if ((newShape->getRefPoint().x - base) < 0 || (newShape->getRefPoint().x + base) > config.windWidth || (newShape->getRefPoint().y - height) < config.toolBarHeight || (newShape->getRefPoint().y + height) > (config.windHeight - config.statusBarHeight)) {
		return false;
	}


	if (shapeCount > 0) {
		for (int i = 0; i < shapeCount; i++) {
			if ((newShape->getxmin() > shapeVector[i]->getxmin()) && (newShape->getxmax() < shapeVector[i]->getxmax()) && (newShape->getymin() > shapeVector[i]->getymin()) && (newShape->getymax() < shapeVector[i]->getymax())) {
				cout << "1";
				return false;
			}
			if ((shapeVector[i]->getxmin() > newShape->getxmin()) && (shapeVector[i]->getxmax() < newShape->getxmax()) && (shapeVector[i]->getymin() > newShape->getymin()) && (shapeVector[i]->getymax() < newShape->getymax())) {
				cout << "2";
				return false;
			}
		}



	}

	shapeVector.push_back(newShape);
	shapeCount++;
	cout << "halooo";
	return true;
}

void grid::setActiveShape(shape* actShape)
{
	activeShape = actShape;
}


shape* grid::getActiveShape() const
{
	return activeShape;
}
void grid::editShapeCount()
{
	shapeCount++;
	if (shapeCount > 0)
		activeShape = shapeVector[shapeCount ];
	else
		activeShape = nullptr;
}
void grid::deleteActiveShape()
{
	delete activeShape;
	activeShape = nullptr;
}
void grid::SaveShapes(ofstream& OutFile)
{
	if (shapeCount > 0)
		OutFile << shapeCount<<"\n";
	for (int i = 0; i < shapeCount; i++)
	{
		shapeVector[i]->save(OutFile);
	}
}
void grid::LoadShapes(ifstream& InFile)
{
	int shpcnt;
	InFile >> shpcnt;
	for (int i = 0; i < shpcnt; i++)
	{
		int shptyp,x,y;
		unsigned char red, green, blue;
		InFile >> shptyp>>x>>y>>red>>green>>blue;
		point pnt;
		pnt.x = x;
		pnt.y = y;
		color clr(red, green, blue);
		shape* sh = nullptr;

		switch (shptyp)
		{
		case GUN:
			sh = new Gun(pGame, pnt, clr);
			break;
		case POINTER:
			sh = new pointerToAball(pGame, pnt, clr);
			break;
		case HOS:
			sh = new house(pGame, pnt, clr);
			break;
		case MAN:
			sh = new strawman(pGame, pnt, clr);
			break;
		case  STDBALL:
			sh = new standingball(pGame, pnt, clr);
			break;
		case SIGN:
			sh = new Sign(pGame, pnt, clr);
			break;
		case BAL:
			sh = new Sign(pGame, pnt, clr);
		}
		sh->load(InFile);
		addShape(sh);
	}
}

int grid::getshapecount()const {
	return shapeCount;
}
vector<shape*> grid::getshapeVector()const {
	return shapeVector;
}