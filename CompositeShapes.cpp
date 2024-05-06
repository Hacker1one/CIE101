#include "CompositeShapes.h"
#include "shape.h"
#include "gameConfig.h"

////////////////////////////////////////////////////  class Sign  ///////////////////////////////////////
Sign::Sign(game* r_pGame, point ref):shape(r_pGame, ref)
{
	topRef = RefPoint;
	baseRef = { RefPoint.x, RefPoint.y + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
	top = new Rect(pGame, topRef, config.sighShape.topHeight, config.sighShape.topWdth);
	base = new Rect(pGame, baseRef, config.sighShape.baseHeight, config.sighShape.baseWdth);
	
	
}
void Sign::draw()   
{
	if ((RefPoint.x - top->getwidth() / 2 > 0) && (RefPoint.x + top->getwidth() / 2 < config.windWidth) && (RefPoint.y + base->getheight() + top->getheight() / 2 < (config.windHeight - config.statusBarHeight)) && (RefPoint.y - top->getheight() / 2 > config.toolBarHeight)) {
		topRef = RefPoint;
		baseRef = { RefPoint.x ,RefPoint.y + (base->getheight() / 2 + top->getheight() / 2) };
		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
		base->draw();
		top->draw();
	}
	else {
		base->draw();
		top->draw();
	}
		
}
void Sign::Flip() {
	if (!flipped) {
		RefPoint.x -= top->getwidth();
		flipped = true;
	}
	else {
		RefPoint.x += top->getwidth();
		flipped = false;
		
	}
		
	
}
ShapeType Sign::getShapeType() const
{
	return SIGN;
}
void Sign::move(char key) {
	point newRef;
	switch ( key) {
	case 2 :                      //Down arrow
		newRef = { this->getRefPoint().x,this->getRefPoint().y+config.gridSpacing };
		if (newRef.y+ base->getheight() + top->getheight()/ 2 < (config.windHeight - config.statusBarHeight))
		this->setRefPoint(newRef);
		break;
	case 4 :                      //Left arrow
		newRef = { this->getRefPoint().x- config.gridSpacing,this->getRefPoint().y   };
		if (newRef.x - top->getwidth() / 2 > 0)
		this->setRefPoint(newRef);
		break;
	case 6 :                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x+top->getwidth()/2<config.windWidth)
		this->setRefPoint(newRef);
		break;
	case 8 :                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - top->getheight()/2 > config.toolBarHeight)
		this->setRefPoint(newRef);
		break;

	}
}
void Sign::resizeUp()
{
	top->resizeUp();
	base->resizeUp();
}
void Sign::resizeDown()
{
	top->resizeDown();
	base->resizeDown();
}
void Sign::Rotate() {
	
	switch (rotated){
	case 0 :
		topRef = RefPoint;
		baseRef = { RefPoint.x - config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2, RefPoint.y };
		rotated = 1;
		break;

	case 1 :
		topRef = RefPoint;
		baseRef = { RefPoint.x , RefPoint.y - config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2 };
		rotated =2;
		break;
	case 2 :
		topRef = RefPoint;
		baseRef = { RefPoint.x + config.sighShape.topHeight / 2 + config.sighShape.baseHeight / 2, RefPoint.y };
		rotated =3;
		break;
	case 4:

		rotated = 0;
		break;
	}

	
}




pointerToAball::pointerToAball(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	 ptrbdyref = { ref.x -  (config.tip.tipheight + config.bdy.bdylength)/2 ,ref.y };
	 ballref = { ref.x + (config.tip.tipheight)/2 + config.ball.ballradius , ref.y };
	 ptrtipref = ref;

	Ptrbdy = new Rect(pGame, ptrbdyref, config.bdy.bdywidth, config.bdy.bdylength);
	ball = new circle(pGame, ballref, config.ball.ballradius);
	ptrtip = new Triangle(pGame, ptrtipref, config.tip.tipwidth, config.tip.tipheight);
	ptrtip->Rotate();
	

}
void pointerToAball::draw() 
{
	Ptrbdy->setRefPoint(ptrbdyref);
	ptrtip->setRefPoint(ptrtipref);
	ball->setRefPoint(ballref);

	Ptrbdy->draw();
	ball->draw();
	ptrtip->draw();
}
void pointerToAball::Flip() {
	if (!flipped) {
		axis = RefPoint.x - (Ptrbdy->getwidth() + ptrtip->getheight()/2);
		RefPoint.x -= 2*(RefPoint.x - axis);
		ptrbdyref.x-=2*(ptrbdyref.x-axis);
		ballref.x -= 2*(ballref.x - axis);
		ptrtip->setAxis(axis);
		ptrtip->Flip();
		flipped = true;

	}
	else {
		axis = RefPoint.x + (Ptrbdy->getwidth() + ptrtip->getheight() / 2);
		RefPoint.x -= 2*(RefPoint.x - axis);
		ptrbdyref.x -= 2*(ptrbdyref.x - axis);
		ballref.x -= 2*(ballref.x - axis);
		ptrtip->Flip();
		flipped = false;
	}
	
}
void pointerToAball::Rotate() {


	if (rotated == 0)
	{
		ptrbdyref = { RefPoint.x, RefPoint.y - (ptrtip->getheight() + Ptrbdy->getwidth()) / 2 };
		ballref = { RefPoint.x , RefPoint.y + (ptrtip->getheight()) / 2 + ball->getradius() };
		ptrtipref = RefPoint;
		Ptrbdy->Rotate();
		ball->Rotate();
		
		ptrtip->Rotate();

		rotated += 1;
		
	}
	else if (rotated == 1)
	{

		ptrbdyref = { RefPoint.x + (ptrtip->getheight() + Ptrbdy->getheight()) / 2 , RefPoint.y };
		ballref = { RefPoint.x - (ptrtip->getheight()) / 2 - ball->getradius(), RefPoint.y };
		ptrtipref = RefPoint;
		Ptrbdy->Rotate();
		ball->Rotate();
		ptrtip->setnrefr(ptrtipref);
		ptrtip->Rotate();
		

		rotated += 1;
	

	}
	else if (rotated == 2)
	{

		ptrbdyref = { RefPoint.x, RefPoint.y + (ptrtip->getheight() + Ptrbdy->getwidth()) / 2 };
		ballref = { RefPoint.x , RefPoint.y - (ptrtip->getheight()) / 2 - ball->getradius() };
		ptrtipref = RefPoint;
		Ptrbdy->Rotate();
		ball->Rotate();
		ptrtip->setnrefr(ptrtipref);
		ptrtip->Rotate();
		

		rotated += 1;
		
	}
	else if (rotated == 3)
	{
		ptrbdyref = { RefPoint.x - (ptrtip->getheight()+ Ptrbdy->getheight() )/2,RefPoint.y };
		ballref = { RefPoint.x + (ptrtip->getheight()) / 2 + ball->getradius() , RefPoint.y };
		ptrtipref = RefPoint;
		Ptrbdy->Rotate();
		ball->Rotate();
		ptrtip->setnrefr(ptrtipref);
		ptrtip->Rotate();

		
		rotated = 0;
		
	}


}
ShapeType pointerToAball::getShapeType() const
{
	return POINTER;
}
void pointerToAball::move(char key) {
	point newRef;
	switch (key) {
	case 2:                      //Down arrow
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };
		if (newRef.y + (config.tip.tipheight) / 2 < (config.windHeight - config.statusBarHeight))
			this->setRefPoint(newRef);
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - config.tip.tipheight/2 - config.bdy.bdylength  > 0)
			this->setRefPoint(newRef);
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + config.tip.tipheight / 2 + config.ball.ballradius*2 < config.windWidth)
			this->setRefPoint(newRef);
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (config.tip.tipheight) / 2 > config.toolBarHeight)
			this->setRefPoint(newRef);
		break;

	}
}
void pointerToAball::resizeUp() {
	ptrbdyref = { RefPoint.x - (ptrtip->getheight() + Ptrbdy->getwidth()) ,RefPoint.y};
	ballref = { RefPoint.x + (ptrtip->getheight()) + 2*ball->getradius() , RefPoint.y};
	ptrtipref = RefPoint;

	Ptrbdy->setRefPoint(ptrbdyref);
	ptrtip->setRefPoint(ptrtipref);
	ball->setRefPoint(ballref);
	Ptrbdy->resizeUp();
	ptrtip->resizeUp();
	ball->resizeUp();
}
void pointerToAball::resizeDown() {
	ptrbdyref = { RefPoint.x - (ptrtip->getheight() + Ptrbdy->getwidth())/4 ,RefPoint.y };
	ballref = { RefPoint.x + (ptrtip->getheight())/4 + ball->getradius()/2 , RefPoint.y };
	ptrtipref = RefPoint;

	Ptrbdy->setRefPoint(ptrbdyref);
	ptrtip->setRefPoint(ptrtipref);
	ball->setRefPoint(ballref);
	Ptrbdy->resizeDown();
	ptrtip->resizeDown();
	ball->resizeDown();
}



standingball::standingball(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	 standref = ref;
	 ballref = { ref.x  , ref.y - (config.stand.standlength / 2 + config.ball.ballradius) };


	stand = new Rect(pGame, standref, config.stand.standwidth, config.stand.standlength);
	ball = new circle(pGame, ballref, config.ball.ballradius);


}
void  standingball::draw() {
	if ((RefPoint.y + stand->getheight() / 2 < (config.windHeight - config.statusBarHeight)) && (RefPoint.x - stand->getwidth() / 2 > 0) && (RefPoint.x + stand->getwidth() / 2 < config.windWidth) && (RefPoint.y - (stand->getwidth() + ball->getradius()) > config.toolBarHeight)) {
		standref = RefPoint;
		ballref = { RefPoint.x  , RefPoint.y - (stand->getwidth() / 2 + ball->getradius()) };
		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->draw();
		ball->draw();
	}
	else {
		stand->draw();
		ball->draw();
	}

}
void standingball::Flip () {
	if (!flipped) {
		RefPoint.x -= stand->getwidth();
		flipped = true;
	}
	else {

		RefPoint.x += stand->getwidth();
		flipped = false;
	}
	

}
void standingball::Rotate() {


	if (rotated == 0)
	{
		standref = RefPoint;
		ballref = { standref.x + (config.stand.standlength / 2 + config.ball.ballradius) , standref.y };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);

		rotated += 1;

	}
	else if (rotated == 1)
	{

		standref = RefPoint;
		ballref = { standref.x  , standref.y + (config.stand.standlength / 2 + config.ball.ballradius) };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);

		rotated += 1;

	}
	else if (rotated == 2)
	{
		standref = RefPoint;
		ballref = { standref.x - (config.stand.standlength / 2 + config.ball.ballradius) , standref.y };


		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);

		rotated += 1;

	}
	else if (rotated == 3)
	{
		standref = RefPoint;
		ballref = { standref.x  , standref.y - (stand->getwidth() / 2 + ball->getradius()) };
		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->draw();
		ball->draw();
		rotated = 0;
	}

	stand->draw();
	ball->draw();
}
ShapeType standingball::getShapeType() const
{
	return STDBALL;
}
void standingball::move(char key) {
	point newRef;
	switch (key) {
	case 2:                      //Down arrow
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };

		if (newRef.y + stand->getheight()/2 < (config.windHeight - config.statusBarHeight))
			this->setRefPoint(newRef);
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - stand->getwidth() /2 > 0)
			this->setRefPoint(newRef);
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + stand->getwidth()/2 < config.windWidth)
			this->setRefPoint(newRef);
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (stand->getwidth() + ball->getradius())  > config.toolBarHeight )
			this->setRefPoint(newRef);
		break;

	}
}
void standingball::resizeUp() {
	standref = RefPoint;
	ballref = { standref.x  , standref.y - (stand->getwidth() + 2 * ball->getradius())};
	stand->setRefPoint(standref);
	ball->setRefPoint(ballref);
	stand->resizeUp();
	ball->resizeUp();
}
void standingball::resizeDown() {
	standref = RefPoint;
	ballref = { standref.x  , standref.y - (stand->getwidth() /4 + ball->getradius()/2) };
	stand->setRefPoint(standref);
	ball->setRefPoint(ballref);
	stand->resizeDown();
	ball->resizeDown();
}



strawman::strawman(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	bodyref = ref;
	hand1ref = { ref.x +  config.strawman.bodywidth/2, ref.y };
    hand2ref = { ref.x -  config.strawman.bodywidth/2, ref.y };;
	leg1ref = { ref.x +   config.strawman.bodywidth/4, ref.y + (config.strawman.bodyheight/2) };
	leg2ref = { ref.x - config.strawman.bodywidth/4, ref.y + (config.strawman.bodyheight)/2 };
	faceref = { ref.x,ref.y -  (config.strawman.faceradius + config.strawman.bodyheight)/2 };

	body = new Triangle(pGame, bodyref, config.strawman.bodywidth, config.strawman.bodyheight);
	hand1 = new Rect(pGame, hand1ref, config.strawman.handwidth, config.strawman.handlength);
	hand2 = new Rect(pGame, hand2ref, config.strawman.handwidth, config.strawman.handlength);
	Leg1 = new Triangle(pGame, leg1ref, config.strawman.legwidth, config.strawman.legheight);
	Leg2 = new Triangle(pGame, leg2ref, config.strawman.legwidth, config.strawman.legheight);
	Face = new circle(pGame, faceref, config.strawman.faceradius);
}
void strawman::draw() 
{
	bodyref = RefPoint;
	hand1ref = { RefPoint.x + body->getbase() / 2, RefPoint.y };
	hand2ref = { RefPoint.x - body->getbase() / 2, RefPoint.y };
	leg1ref = { RefPoint.x + body->getbase() / 4, RefPoint.y + (body->getheight() / 2) };
	leg2ref = { RefPoint.x - body->getbase() / 4, RefPoint.y + (body->getheight() / 2) };
	faceref = { RefPoint.x,RefPoint.y - (Face->getradius() / 2 + body->getheight() / 2) };
	body->setRefPoint(bodyref);
	hand1->setRefPoint(hand1ref);
	hand2->setRefPoint(hand2ref);
	Leg1->setRefPoint(leg1ref);
	Leg2->setRefPoint(leg2ref);
	Face->setRefPoint(faceref);
	body->draw();
	hand1->draw();
	hand2->draw();
	Leg1->draw();
	Leg2->draw();
	Face->draw();
}
void strawman::Flip() {
	bodyref = { RefPoint.x - body->getbase() , RefPoint.y };;
	hand1ref = { bodyref.x + body->getbase() / 2, RefPoint.y };
	hand2ref = { bodyref.x - body->getbase() / 2, RefPoint.y };;
	leg1ref = { bodyref.x + body->getbase() / 4, RefPoint.y + (body->getheight() / 2) };
	leg2ref = { bodyref.x - body->getbase() / 4, RefPoint.y + (body->getheight() / 2) };
	faceref = { bodyref.x,RefPoint.y - (Face->getradius() + body->getheight()) / 2 };
		body->setRefPoint(bodyref);
		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		
	

}
void strawman::Rotate() {

	if (rotated == 0)
	{
		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y + config.strawman.bodywidth / 2 };
		hand2ref = { RefPoint.x, RefPoint.y - config.strawman.bodywidth / 2 };
		leg1ref = { RefPoint.x - (config.strawman.bodyheight / 2 , RefPoint.y + config.strawman.bodywidth / 4) };
		leg2ref = { RefPoint.x - (config.strawman.bodyheight) / 2, RefPoint.y - config.strawman.bodywidth / 4 };
		faceref = { RefPoint.x + (config.strawman.faceradius + config.strawman.bodyheight) / 2 ,RefPoint.y };

		body->setRefPoint(bodyref);
		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);


		rotated += 1;

	}
	else if (rotated == 1)
	{

		bodyref = RefPoint;
		hand1ref = { RefPoint.x - config.strawman.bodywidth / 2, RefPoint.y };
		hand2ref = { RefPoint.x + config.strawman.bodywidth / 2, RefPoint.y };
		leg1ref = { RefPoint.x - config.strawman.bodywidth / 4, RefPoint.y - (config.strawman.bodyheight / 2) };
		leg2ref = { RefPoint.x + config.strawman.bodywidth / 4, RefPoint.y - (config.strawman.bodyheight) / 2 };
		faceref = { RefPoint.x,RefPoint.y + (config.strawman.faceradius + config.strawman.bodyheight) / 2 };

		body->setRefPoint(bodyref);
		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);


		rotated += 1;

	}
	else if (rotated == 2)
	{

		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y - config.strawman.bodywidth / 2 };
		hand2ref = { RefPoint.x, RefPoint.y + config.strawman.bodywidth / 2 };
		leg1ref = { RefPoint.x + (config.strawman.bodyheight / 2 , RefPoint.y - config.strawman.bodywidth / 4) };
		leg2ref = { RefPoint.x + (config.strawman.bodyheight) / 2, RefPoint.y + config.strawman.bodywidth / 4 };
		faceref = { RefPoint.x - (config.strawman.faceradius + config.strawman.bodyheight) / 2 ,RefPoint.y };

		body->setRefPoint(bodyref);
		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);


		rotated += 1;

	}
	else if (rotated == 3)
	{
		this->draw();
		rotated = 0;
	}


	body->draw();
	hand1->draw();
	hand2->draw();
	Leg1->draw();
	Leg2->draw();
	Face->draw();
}
ShapeType strawman::getShapeType() const
{
	return MAN;
}
void strawman::move(char key) {
	point newRef;
	switch (key) {
	case 2:                      //Down arrow
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };

		if (newRef.y + (config.strawman.bodyheight) < (config.windHeight - config.statusBarHeight))
			this->setRefPoint(newRef);
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - config.strawman.handlength > 0)
			this->setRefPoint(newRef);
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + config.strawman.handlength < config.windWidth)
			this->setRefPoint(newRef);
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (config.strawman.faceradius*2 + config.strawman.bodyheight/2) > config.toolBarHeight)
			this->setRefPoint(newRef);
		break;

	}
}
void strawman::resizeUp() {
	bodyref = RefPoint;
	hand1ref = { RefPoint.x + body->getbase(), RefPoint.y };
	hand2ref = { RefPoint.x - body->getbase(), RefPoint.y };
	leg1ref = { RefPoint.x + body->getbase() / 2, RefPoint.y + (body->getheight()) };
	leg2ref = { RefPoint.x - body->getbase() / 2, RefPoint.y + (body->getheight()) };
	faceref = { RefPoint.x,RefPoint.y - (Face->getradius() + body->getheight())};
	body->setRefPoint(bodyref);
	hand1->setRefPoint(hand1ref);
	hand2->setRefPoint(hand2ref);
	Leg1->setRefPoint(leg1ref);
	Leg2->setRefPoint(leg2ref);
	Face->setRefPoint(faceref);
	body->resizeUp();
	hand1->resizeUp();
	hand2->resizeUp();
	Leg1->resizeUp();
	Leg2->resizeUp();
	Face->resizeUp();
}
void strawman::resizeDown() {
	bodyref = RefPoint;
	hand1ref = { RefPoint.x + body->getbase() / 4, RefPoint.y };
	hand2ref = { RefPoint.x - body->getbase() / 4, RefPoint.y };
	leg1ref = { RefPoint.x + body->getbase() / 8, RefPoint.y + (body->getheight())/4 };
	leg2ref = { RefPoint.x - body->getbase() / 8, RefPoint.y + (body->getheight())/4 };
	faceref = { RefPoint.x,RefPoint.y - (Face->getradius() + body->getheight())/4 };
	body->setRefPoint(bodyref);
	hand1->setRefPoint(hand1ref);
	hand2->setRefPoint(hand2ref);
	Leg1->setRefPoint(leg1ref);
	Leg2->setRefPoint(leg2ref);
	Face->setRefPoint(faceref);
	body->resizeDown();
	hand1->resizeDown();
	hand2->resizeDown();
	Leg1->resizeDown();
	Leg2->resizeDown();
	Face->resizeDown();
}




Gun::Gun(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	bodyref = ref;
	bullet1ref = { ref.x + 6 * config.Gun.BodyLength/5, ref.y };
	bullet2ref = { ref.x + 3* config.Gun.BodyLength/2, ref.y };
	handref = { ref.x - (config.Gun.BodyLength / 2 - config.Gun.GetHeight / 2) , ref.y + (config.Gun.GetBase/2+ config.Gun.BodyWidth/2) };

	body = new Rect(pGame, bodyref, config.Gun.BodyWidth, config.Gun.BodyLength);
	bullet1 = new circle(pGame, bullet1ref, config.Gun.BulletRadius);
	bullet2 = new circle(pGame, bullet2ref, config.Gun.BulletRadius);

	hand = new Triangle(pGame, handref, config.Gun.GetBase, config.Gun.GetHeight);
}
void Gun::draw() 
{
	bodyref = RefPoint;
	bullet1ref = { RefPoint.x + 6 * body->getwidth() / 5, RefPoint.y };
	bullet2ref = { RefPoint.x + 3 * body->getwidth() / 2, RefPoint.y };
	handref = { RefPoint.x - (body->getwidth() / 2 - body->getheight() / 2) , RefPoint.y - (hand->getbase() / 2 + body->getheight() / 2) };
	body->setRefPoint(bodyref);
	bullet1->setRefPoint(bullet1ref);
	bullet2->setRefPoint(bullet2ref);
	hand->setRefPoint(handref);
	
}

void Gun::Flip() {
	bodyref = {RefPoint.x- body->getwidth() ,RefPoint.y};
	bullet1ref = { bodyref.x- (6 * body->getwidth() / 5), RefPoint.y };
	bullet2ref = { bodyref.x - 3 * body->getwidth() / 2, RefPoint.y };
	handref = { bodyref.x + body->getwidth() /2 - body->getheight() / 2, RefPoint.y - (hand->getbase() / 2 + body->getheight() / 2) };
		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);
		
	

}
void Gun::Rotate() {

	if (rotated == 0)
	{
		bodyref = RefPoint;
		bullet1ref = { RefPoint.x , RefPoint.y + 6 * config.Gun.BodyLength / 5 };
		bullet2ref = { RefPoint.x , RefPoint.y + 3 * config.Gun.BodyLength / 2 };
		handref = { RefPoint.x - (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2), RefPoint.y - (config.Gun.BodyLength / 2 - config.Gun.GetHeight / 2) };


		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);


		rotated += 1;

	}
	else if (rotated == 1)
	{

		bodyref = RefPoint;
		bullet1ref = { RefPoint.x - 6 * config.Gun.BodyLength / 5, RefPoint.y };
		bullet2ref = { RefPoint.x - 3 * config.Gun.BodyLength / 2, RefPoint.y };
		handref = { RefPoint.x + (config.Gun.BodyLength / 2 - config.Gun.GetHeight / 2), RefPoint.y - (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2) };

		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);


		rotated += 1;

	}
	else if (rotated == 2)
	{

		bodyref = RefPoint;
		bullet1ref = { RefPoint.x , RefPoint.y - 6 * config.Gun.BodyLength / 5 };
		bullet2ref = { RefPoint.x , RefPoint.y - 3 * config.Gun.BodyLength / 2 };
		handref = { RefPoint.x + (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2), RefPoint.y + (config.Gun.BodyLength / 2 - config.Gun.GetHeight / 2) };


		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);


		rotated += 1;

	}
	else if (rotated == 3)
	{
		this->Rotate();
		rotated = 0;
	}


	body->draw();
	bullet1->draw();
	bullet2->draw();
	hand->draw();
}
ShapeType Gun::getShapeType()const
{
	return GUN;
}
void Gun::move(char key) {
	point newRef;
	switch (key) {
	case 2:                      //Down arrow
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };

		if (newRef.y + config.Gun.BodyWidth / 2 < (config.windHeight - config.statusBarHeight))
			this->setRefPoint(newRef);
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - config.Gun.BodyLength/2 > 0)
			this->setRefPoint(newRef);
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x +2* config.Gun.BodyLength  < config.windWidth)
			this->setRefPoint(newRef);
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - config.Gun.BodyWidth/2 - config.Gun.GetHeight/2 > config.toolBarHeight)
			this->setRefPoint(newRef);
		break;
	}

}
void Gun::resizeUp() {
	bodyref = RefPoint;
	bullet1ref = { RefPoint.x + 12 * body->getwidth() / 5, RefPoint.y };
	bullet2ref = { RefPoint.x + 6* body->getwidth() / 2, RefPoint.y };
	handref = { RefPoint.x - (body->getwidth() - body->getheight()) , RefPoint.y+(hand->getbase()+body->getheight())};
	body->setRefPoint(bodyref);
	bullet1->setRefPoint(bullet1ref);
	bullet2->setRefPoint(bullet2ref);
	hand->setRefPoint(handref);
	body->resizeUp();
	bullet1->resizeUp();
	bullet2->resizeUp();
	hand->resizeUp();
}
void Gun::resizeDown() {
	bodyref = RefPoint;
	bullet1ref = { RefPoint.x + 6 * body->getwidth() / 10, RefPoint.y };
	bullet2ref = { RefPoint.x + 3 * body->getwidth() / 4, RefPoint.y };
	handref = { RefPoint.x - (body->getwidth() - body->getheight()) / 4, RefPoint.y + (hand->getbase() + body->getheight())/4 };
	body->setRefPoint(bodyref);
	bullet1->setRefPoint(bullet1ref);
	bullet2->setRefPoint(bullet2ref);
	hand->setRefPoint(handref);
	body->resizeDown();
	bullet1->resizeDown();
	bullet2->resizeDown();
	hand->resizeDown();
}



house::house(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	bodyref = ref;
	roofref = { ref.x , ref.y - (config.house.bodyheight / 2 + config.house.roofheight / 2) };
	body = new Rect(pGame, bodyref, config.house.bodyheight, config.house.bodyLength);
	roof = new Triangle(pGame, roofref, config.house.roofwidth, config.house.roofheight);

}
void house::draw()
{
	bodyref = RefPoint;
	roofref = { RefPoint.x , RefPoint.y - (body->getheight() / 2 + roof->getheight() / 2) };
	body->setRefPoint(bodyref);
	roof->setRefPoint(roofref);

}
void house::Flip()
{
	if (!flipped) {
		bodyref = { RefPoint.x - body->getwidth(), RefPoint.y };
		roofref = { bodyref.x , RefPoint.y - (body->getheight() + roof->getheight()) / 2 };

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);
		flipped = true;
	}
	else {

		RefPoint = { RefPoint.x + body->getwidth(), RefPoint.y };
		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y - (body->getheight() + roof->getheight()) / 2 };

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);
		flipped = false;
	}
}
void house::Rotate() {

	if (rotated == 0)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x + (config.house.bodyheight + config.house.roofheight) / 2, RefPoint.y };

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

		rotated += 1;

	}
	else if (rotated == 1)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y + (config.house.bodyheight + config.house.roofheight) / 2 };

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

		rotated += 1;

	}
	else if (rotated == 2)
	{
		bodyref = RefPoint;
		roofref = { RefPoint.x - (config.house.bodyheight + config.house.roofheight) / 2, RefPoint.y };

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

		rotated += 1;

	}
	else if (rotated == 3)
	{
		this->draw();
		rotated = 0;
	}


	body->draw();
	roof->draw();
}
ShapeType house::getShapeType()const
{
	return HOS;
}
void house::move(char key) {
	point newRef;
	switch (key) {
	case 2:                      //Down arrow
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };

		if (newRef.y + config.house.bodyheight / 2 < (config.windHeight - config.statusBarHeight))
			this->setRefPoint(newRef);
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - config.house.roofwidth / 2 > 0)
			this->setRefPoint(newRef);
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + config.house.roofwidth / 2 < config.windWidth)
			this->setRefPoint(newRef);
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (config.house.bodyheight+ config.house.roofheight)/2 - 20 > config.toolBarHeight)
			this->setRefPoint(newRef);
		break;
	}

}
void house::resizeUp()
{

	bodyref = RefPoint;
	roofref = { RefPoint.x , RefPoint.y - (body->getheight() + roof->getheight())};
	body->setRefPoint(bodyref);
	roof->setRefPoint(roofref);
	body->resizeUp();
	roof->resizeUp();
}
void house::resizeDown()
{

	bodyref = RefPoint;
	roofref = { RefPoint.x , RefPoint.y - (body->getheight() + roof->getheight()) / 4};
	body->setRefPoint(bodyref);
	roof->setRefPoint(roofref);
	body->resizeDown();
	roof->resizeDown();
}




balance::balance(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	circRef = { RefPoint.x , RefPoint.y - (config.balance.getRectWidth / 2 + config.balance.getradius) };
	triRef = { RefPoint.x  , RefPoint.y + (config.balance.getTRIheight + config.balance.getRectWidth) / 2 };
	rec = new Rect(pGame, recRef, config.balance.getRectWidth, config.balance.GetRectHeight);
	tri = new Triangle(pGame, triRef, config.balance.getTRIheight, config.balance.getTRIBase);
	circ = new circle(pGame, circRef, config.balance.getradius);
	circRef = { RefPoint.x , RefPoint.y - (rec->getheight() / 2 + circ->getradius()) };
	triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() / 2 + rec->getheight() / 2) };

}
void balance::draw()
{
	
	rec->setRefPoint(RefPoint);
	circ->setRefPoint(circRef);
	tri->setRefPoint(triRef);
	rec->draw();
	tri->draw();
	circ->draw();
	
}
void balance::Flip()
{
	if (!flipped) {
		RefPoint = { RefPoint.x - rec->getwidth(),RefPoint.y };
		circRef = { RefPoint.x  , RefPoint.y - (rec->getheight() / 2 + circ->getradius()) };
		triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() + rec->getheight()) / 2 };
		flipped = true;
	}
	else {
		RefPoint = { RefPoint.x + rec->getwidth(),RefPoint.y };
		circRef = { RefPoint.x , RefPoint.y - (rec->getheight() / 2 + circ->getradius()) };
		triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() + rec->getheight()) / 2 };
		flipped = false;
	}

	
	
}
void balance::Rotate() {


	if (rotated == 0)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x + (config.balance.getRectWidth / 2 + config.balance.getradius) , RefPoint.y };
		triRef = { RefPoint.x - (config.balance.getTRIheight + config.balance.getRectWidth) / 2 , RefPoint.y };

		rec->setRefPoint(recRef);
		circ->setRefPoint(circRef);
		tri->setRefPoint(triRef);

		rotated += 1;

	}
	else if (rotated == 1)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x , RefPoint.y + (config.balance.getRectWidth / 2 + config.balance.getradius) };
		triRef = { RefPoint.x  , RefPoint.y - (config.balance.getTRIheight + config.balance.getRectWidth) / 2 };

		rec->setRefPoint(recRef);
		circ->setRefPoint(circRef);
		tri->setRefPoint(triRef);

		rotated += 1;

	}
	else if (rotated == 2)
	{
		recRef = RefPoint;
		circRef = { RefPoint.x - (config.balance.getRectWidth / 2 + config.balance.getradius) , RefPoint.y };
		triRef = { RefPoint.x + (config.balance.getTRIheight + config.balance.getRectWidth) / 2 , RefPoint.y };

		rec->setRefPoint(recRef);
		circ->setRefPoint(circRef);
		tri->setRefPoint(triRef);

		rotated += 1;

	}
	else if (rotated == 3)
	{
		circRef = { RefPoint.x - (config.balance.getRectWidth / 2 + config.balance.getradius) , RefPoint.y };
		triRef = { RefPoint.x + (config.balance.getTRIheight + config.balance.getRectWidth) / 2 , RefPoint.y };
		

		rec->setRefPoint(recRef);
		circ->setRefPoint(circRef);
		tri->setRefPoint(triRef);
		rotated = 0;
	}

	rec->draw();
	circ->draw();
	tri->draw();
}
ShapeType balance::getShapeType()const
{
	return HOS;
}
void balance::move(char key) {
	point newRef;
	switch (key) {
	case 2:                      //Down arrow
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };

		if (newRef.y + (config.balance.getRectWidth/2 + config.balance.getTRIheight) < (config.windHeight - config.statusBarHeight))
			this->setRefPoint(newRef);
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - config.balance.GetRectHeight / 2 > 0)
			this->setRefPoint(newRef);
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + config.balance.GetRectHeight / 2 < config.windWidth)
			this->setRefPoint(newRef);
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (config.balance.getRectWidth / 2 +2 * config.balance.getradius) > config.toolBarHeight)
			this->setRefPoint(newRef);
		break;
	}

}
void balance::resizeUp()
{

	recRef = RefPoint;
	circRef = { RefPoint.x , RefPoint.y - (rec->getheight() + 2 * circ->getradius())};
	triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() + rec->getheight())};
	rec->setRefPoint(recRef);
	circ->setRefPoint(circRef);
	tri->setRefPoint(triRef);
	rec->resizeUp();
	tri->resizeUp();
	circ->resizeUp();
}
void balance::resizeDown()
{

	recRef = RefPoint;
	circRef = { RefPoint.x , RefPoint.y - (rec->getheight() /4 + circ->getradius() /2) };
	triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() + rec->getheight()) / 4 };
	rec->setRefPoint(recRef);
	circ->setRefPoint(circRef);
	tri->setRefPoint(triRef);
	rec->resizeDown();
	tri->resizeDown();
	circ->resizeDown();
}