#pragma once
#include <string>
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration

struct point
{
	int x, y;

};

enum ShapeType
{
	//Basic shapes
	RCT,	//rectangle
	CRC,	//circle
	TRI,	//triangle
	POINTER,
	HOS,
	GUN,
	MAN,
	STDBALL,
    SIGN,	
	BAL
	

	//TODO: Add more types
};


class shape
{
protected:
	point RefPoint;		//Each shape must have a reference point
    game* pGame;        //pointer to game object
	color fillColor;	//shape fill color
	color borderColor;	//shape border color
	bool flipped;
	int rotated ;
int resized;
	int axis;
public:
	shape(game* r_pGame, point ref);
    virtual void draw() =0;//for a shape to draw itself on the screen
	void setRefPoint(point p);
	point getRefPoint();
	virtual void Rotate()=0;
	bool GetFlipStatus();
	virtual ShapeType getShapeType() const = 0;
	virtual void move(char) = 0;                            //Move the shape
	virtual void resizeUp() = 0;
	virtual void resizeDown() = 0;
	virtual void Flip() = 0;
	virtual void save(ofstream& OutFile) = 0;
							  
	//-- The following functions should be supported by the shape class
	//-- It should be overridden by each inherited shape
	//-- Decide the parameters that you should pass to each function	


	
		//Save the shape parameters to the file
	//virtual void load(ifstream &Infile) = 0;	//Load the shape parameters to the file

};




