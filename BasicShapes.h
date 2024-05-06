//Header file for Basic shapes in the game
#pragma once
#include "shape.h"



class Rect:public shape
{
	int hght, wdth;	//height and width of the recangle
	
	point upperLeft, lowerBottom;
public:
	Rect(game* r_pGame, point ref, int r_hght, int r_wdth);
	virtual void draw() ;
	virtual void Rotate() override;
	int getheight();
	int getwidth();
	virtual ShapeType getShapeType() const;
	virtual void move(char);
	virtual void resizeUp();
	virtual void resizeDown();
	virtual void Flip() override;
};




class circle :public shape
{
	//Add data memebrs for class circle
	int rad;
	

public:
	circle(game* r_pGame, point ref, int r);	//add more parameters for the constructor if needed
	virtual void draw()  override ;
	virtual void Flip();
	virtual void Rotate() override;
	int getradius();
	virtual ShapeType getShapeType() const;
	virtual void move(char);
	virtual void resizeUp();
	virtual void resizeDown();

};



class Triangle : public shape
{
	int base, height;
	point vertix1,vertix2,vertix3,nrefr;


public:
	Triangle(game* r_pGame, point ref, int r_base, int r_height);
	virtual void draw() override;
	virtual void Flip();
	virtual void Rotate() override;
	virtual void resizeUp() override;
	virtual void resizeDown() override;
	int getheight();
	int getbase();
	virtual ShapeType getShapeType() const;
	virtual void move(char);
	void setAxis(int);
	void setnrefr(point);
};