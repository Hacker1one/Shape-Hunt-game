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
	

		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
		base->draw();
		top->draw();
	
	
		
}
void Sign::Flip() {
	if (!flipped) {
		axis = RefPoint.x - top->getwidth()/2;
		RefPoint.x -= 2 * (RefPoint.x - axis);
		topRef.x -= 2 * (topRef.x - axis);
		baseRef.x -= 2 * (baseRef.x - axis);
		flipped = true;

	}
	else {
		axis = RefPoint.x + top->getwidth() /2;
		RefPoint.x -= 2 * (RefPoint.x - axis);
		topRef.x -= 2 * (topRef.x - axis);
		baseRef.x -= 2 * (baseRef.x - axis);
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
		if (newRef.y + base->getheight() + top->getheight() / 2 < (config.windHeight - config.statusBarHeight)) {
			this->setRefPoint(newRef);
			baseRef.y += config.gridSpacing;
			topRef.y += config.gridSpacing;
		}
		break;
	case 4 :                      //Left arrow
		newRef = { this->getRefPoint().x- config.gridSpacing,this->getRefPoint().y   };
		if (newRef.x - top->getwidth() / 2 > 0) {
			this->setRefPoint(newRef);
			baseRef.x -= config.gridSpacing;
			topRef.x -= config.gridSpacing;
		}
		break;
	case 6 :                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + top->getwidth() / 2 < config.windWidth) {
			this->setRefPoint(newRef);
			baseRef.x += config.gridSpacing;
			topRef.x += config.gridSpacing;
		}
		break;
	case 8 :                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - top->getheight() / 2 > config.toolBarHeight) {
			this->setRefPoint(newRef);
			baseRef.y -= config.gridSpacing;
			topRef.y -= config.gridSpacing;
		}
		break;

	}
}
void Sign::resizeUp()
{
	top->resizeUp();
	base->resizeUp();
	resized++;
	point newRef;
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };
		if (newRef.y + base->getheight() + top->getheight() / 2 > (config.windHeight - config.statusBarHeight))
			{
				top->resizeDown();
				base->resizeDown();
				resized--;
		}
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - top->getwidth() / 2 < 0) {
			top->resizeDown();
			base->resizeDown();
			resized--;
		}
		if (newRef.x + top->getwidth() / 2 > config.windWidth) {
			top->resizeDown();
			base->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - top->getheight() / 2 < config.toolBarHeight) {
			top->resizeDown();
			base->resizeDown();
			resized--;
		}
		if (rotated == 1)
		{
			topRef = RefPoint;
			baseRef = { RefPoint.x - top->getheight() / 2 - config.sighShape.baseHeight / 2, RefPoint.y };

			base->setRefPoint(baseRef);
			top->setRefPoint(topRef);
		}
		else if (rotated == 2)
		{
			topRef = RefPoint;
			baseRef = { RefPoint.x , RefPoint.y - top->getheight() / 2 - base->getheight() / 2 };

			base->setRefPoint(baseRef);
			top->setRefPoint(topRef);
		}
		else if (rotated == 3)
		{
			topRef = RefPoint;
			baseRef = { RefPoint.x + top->getheight() / 2 + base->getheight() / 2, RefPoint.y };

			base->setRefPoint(baseRef);
			top->setRefPoint(topRef);
		}
		else if (rotated == 0)
		{
			topRef = RefPoint;
			baseRef = { RefPoint.x, RefPoint.y + top->getheight() / 2 + base->getheight() / 2 };
			base->setRefPoint(baseRef);
			top->setRefPoint(topRef);
		}
}
void Sign::resizeDown()
{
	top->resizeDown();
	base->resizeDown();
	resized--;
	if (rotated == 1)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x - top->getheight() / 2 - config.sighShape.baseHeight / 2, RefPoint.y };

		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
	}
	else if (rotated == 2)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x , RefPoint.y - top->getheight() / 2 - base->getheight() / 2 };

		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
	}
	else if (rotated == 3)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x + top->getheight() / 2 + base->getheight() / 2, RefPoint.y };

		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
	}
	else if (rotated == 0)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x, RefPoint.y + top->getheight() / 2 + base->getheight() / 2 };
		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
	}
}
void Sign::Rotate() {
	

	if (rotated == 0)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x - top->getheight() / 2 - config.sighShape.baseHeight / 2, RefPoint.y };

		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
		base->Rotate();
		top->Rotate();
		rotated += 1;

	
	}
	else if (rotated == 1)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x , RefPoint.y - top->getheight() / 2 - base->getheight() / 2 };

		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
		base->Rotate();
		top->Rotate();
		rotated += 1;

	}
	else if (rotated == 2)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x + top->getheight() / 2 + base->getheight() / 2, RefPoint.y };

		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
		base->Rotate();
		top->Rotate();
		rotated += 1;

		
	}
	else if (rotated == 3)
	{
		topRef = RefPoint;
		baseRef = { RefPoint.x, RefPoint.y + top->getheight() / 2 + base->getheight() / 2 };
		base->setRefPoint(baseRef);
		top->setRefPoint(topRef);
		base->Rotate();
		top->Rotate();
		rotated = 0;

		

	}
}





////////////////////////////////////////////////////  class Pointer To A Ball  //////////////////////////////////////////////////////////////
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
		
		ptrtip->setnrefr(ptrtipref);

		ptrtip->Rotate();
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);

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
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);

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
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);

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
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
		
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
		
		
		if (newRef.y + ptrtip->getheight() / 2 < (config.windHeight - config.statusBarHeight)) {
			this->setRefPoint(newRef);
			ballref.y += config.gridSpacing;
			ptrtipref.y += config.gridSpacing;
			ptrbdyref.y += config.gridSpacing;
			ptrtip->move(key);
		}
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - ptrtip->getheight()/ 2 - Ptrbdy->getwidth() > 0) {
			this->setRefPoint(newRef);
			ballref.x -= config.gridSpacing;
			ptrtipref.x -= config.gridSpacing;
			ptrbdyref.x -= config.gridSpacing;
			ptrtip->move(key);
		}
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + ptrtip->getheight() / 2 + ball->getradius() * 2 < config.windWidth) {
			this->setRefPoint(newRef);
			ballref.x += config.gridSpacing;
			ptrtipref.x += config.gridSpacing;
			ptrbdyref.x += config.gridSpacing;
			ptrtip->move(key);
		}
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (ptrtip->getheight()) / 2 > config.toolBarHeight) {
			this->setRefPoint(newRef);
			ballref.y -= config.gridSpacing;
			ptrtipref.y -= config.gridSpacing;
			ptrbdyref.y -= config.gridSpacing;
			ptrtip->move(key);
		}
		break;

	}
}
void pointerToAball::resizeUp() {
	Ptrbdy->resizeUp();
	ptrtip->resizeUp();
	ball->resizeUp();
	resized++;
	point newRef;
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };
		if (newRef.y + ptrtip->getheight() / 2 > (config.windHeight - config.statusBarHeight))
		{
			Ptrbdy->resizeDown();
			ptrtip->resizeDown();
			ball->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - ptrtip->getheight() / 2 - Ptrbdy->getwidth() < 0)
		{
			Ptrbdy->resizeDown();
			ptrtip->resizeDown();
			ball->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + ptrtip->getheight() / 2 + ball->getradius() * 2 > config.windWidth)
		{
			Ptrbdy->resizeDown();
			ptrtip->resizeDown();
			ball->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (ptrtip->getheight()) / 2 < config.toolBarHeight)
		{
			Ptrbdy->resizeDown();
			ptrtip->resizeDown();
			ball->resizeDown();
			resized--;
		}
	if (rotated == 1) {
		ptrbdyref = { RefPoint.x, RefPoint.y - (ptrtip->getheight() + Ptrbdy->getwidth()) / 2 };
		ballref = { RefPoint.x , RefPoint.y + (ptrtip->getheight()) / 2 + ball->getradius() };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
	if (rotated == 2) {
		ptrbdyref = { RefPoint.x + (ptrtip->getheight() + Ptrbdy->getheight()) / 2 , RefPoint.y };
		ballref = { RefPoint.x - (ptrtip->getheight()) / 2 - ball->getradius(), RefPoint.y };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
	if (rotated == 3) {
		ptrbdyref = { RefPoint.x, RefPoint.y + (ptrtip->getheight() + Ptrbdy->getwidth()) / 2 };
		ballref = { RefPoint.x , RefPoint.y - (ptrtip->getheight()) / 2 - ball->getradius() };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
	if (rotated == 0) {
		ptrbdyref = { RefPoint.x - (ptrtip->getheight() + Ptrbdy->getheight()) / 2,RefPoint.y };
		ballref = { RefPoint.x + (ptrtip->getheight()) / 2 + ball->getradius() , RefPoint.y };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
}
void pointerToAball::resizeDown() {
	Ptrbdy->resizeDown();
	ptrtip->resizeDown();
	ball->resizeDown();
	resized--;
	if (rotated == 1) {
		ptrbdyref = { RefPoint.x, RefPoint.y - (ptrtip->getheight() + Ptrbdy->getwidth()) / 2 };
		ballref = { RefPoint.x , RefPoint.y + (ptrtip->getheight()) / 2 + ball->getradius() };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
	if (rotated == 2) {
		ptrbdyref = { RefPoint.x + (ptrtip->getheight() + Ptrbdy->getheight()) / 2 , RefPoint.y };
		ballref = { RefPoint.x - (ptrtip->getheight()) / 2 - ball->getradius(), RefPoint.y };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
	if (rotated == 3) {
		ptrbdyref = { RefPoint.x, RefPoint.y + (ptrtip->getheight() + Ptrbdy->getwidth()) / 2 };
		ballref = { RefPoint.x , RefPoint.y - (ptrtip->getheight()) / 2 - ball->getradius() };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
	if (rotated == 0) {
		ptrbdyref = { RefPoint.x - (ptrtip->getheight() + Ptrbdy->getheight()) / 2,RefPoint.y };
		ballref = { RefPoint.x + (ptrtip->getheight()) / 2 + ball->getradius() , RefPoint.y };
		ptrtipref = RefPoint;
		Ptrbdy->setRefPoint(ptrbdyref);
		ptrtip->setRefPoint(ptrtipref);
		ball->setRefPoint(ballref);
	}
}






////////////////////////////////////////////////////  class Standing Ball  //////////////////////////////////////////////////////////////
standingball::standingball(game* r_pGame, point ref) :shape(r_pGame, ref)
{
	 standref = ref;
	 ballref = { ref.x  , ref.y - (config.stand.standlength / 2 + config.ball.ballradius) };


	stand = new Rect(pGame, standref, config.stand.standwidth, config.stand.standlength);
	ball = new circle(pGame, ballref, config.ball.ballradius);


}
void  standingball::draw() {
		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->draw();
		ball->draw();
	
	

}
void standingball::Flip () {
	if (!flipped) {
		axis = RefPoint.x - stand->getwidth() / 2;
		RefPoint.x -= 2 * (RefPoint.x - axis);
		standref.x -= 2 * (standref.x - axis);
		ballref.x -= 2 * (ballref.x - axis);
		flipped = true;

	}
	else {
		axis = RefPoint.x + stand->getwidth() / 2;
		RefPoint.x -= 2 * (RefPoint.x - axis);
		standref.x -= 2 * (standref.x - axis);
		ballref.x -= 2 * (ballref.x - axis);
		flipped = false;
	}
	

}
void standingball::Rotate() {

	if (rotated == 0)
	{
		standref = RefPoint;
		ballref = { standref.x + (stand->getwidth() / 2 + ball->getradius()) , standref.y };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->Rotate();

		rotated += 1;



	}
	else if (rotated == 1)
	{

		standref = RefPoint;
		ballref = { standref.x  , standref.y + (stand->getheight() / 2 + ball->getradius()) };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->Rotate();

		rotated += 1;

	}
	else if (rotated == 2)
	{
		standref = RefPoint;
		ballref = { standref.x - (stand->getwidth() / 2 + ball->getradius()) , standref.y };


		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->Rotate();

		rotated += 1;

		

	}
	else if (rotated == 3)
	{
		standref = RefPoint;
		ballref = { standref.x  , standref.y - (stand->getheight() / 2 + ball->getradius()) };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->Rotate();

		rotated = 0;

	}

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

		if (newRef.y + stand->getheight() / 2 < (config.windHeight - config.statusBarHeight)) {
			this->setRefPoint(newRef);
			ballref.y += config.gridSpacing;
			standref.y+= config.gridSpacing;
		}

		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - stand->getwidth() / 2 > 0) {
			this->setRefPoint(newRef);
			ballref.x -= config.gridSpacing;
			standref.x -= config.gridSpacing;
		}
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + stand->getwidth() / 2 < config.windWidth) {
			this->setRefPoint(newRef);
			ballref.x += config.gridSpacing;
			standref.x += config.gridSpacing;
		}
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (stand->getwidth() + ball->getradius()) > config.toolBarHeight) {
			this->setRefPoint(newRef);
			ballref.y -= config.gridSpacing;
			standref.y -= config.gridSpacing;
		}
		break;

	}
}
void standingball::resizeUp() {
	stand->resizeUp();
	ball->resizeUp();
	resized++;
	point newRef;
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };
		if (newRef.y + stand->getheight() / 2 > (config.windHeight - config.statusBarHeight))
		{
			stand->resizeDown();
			ball->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - stand->getwidth() / 2 < 0)
		{
			stand->resizeDown();
			ball->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + stand->getwidth() / 2 > config.windWidth)
		{
			stand->resizeDown();
			ball->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (stand->getwidth() + ball->getradius()) < config.toolBarHeight)
		{
			stand->resizeDown();
			ball->resizeDown();
			resized--;
		}
		if (rotated == 1)
		{
			standref = RefPoint;
			ballref = { standref.x + (stand->getwidth() / 2 + ball->getradius()) , standref.y };

			stand->setRefPoint(standref);
			ball->setRefPoint(ballref);
			stand->Rotate();
		}
		else if (rotated == 2)
		{

			standref = RefPoint;
			ballref = { standref.x  , standref.y + (stand->getheight() / 2 + ball->getradius()) };

			stand->setRefPoint(standref);
			ball->setRefPoint(ballref);
		}
		else if (rotated == 3)
		{
			standref = RefPoint;
			ballref = { standref.x - (stand->getwidth() / 2 + ball->getradius()) , standref.y };


			stand->setRefPoint(standref);
			ball->setRefPoint(ballref);

		}
		else if (rotated == 0)
		{
			standref = RefPoint;
			ballref = { standref.x  , standref.y - (stand->getheight() / 2 + ball->getradius()) };

			stand->setRefPoint(standref);
			ball->setRefPoint(ballref);

		}
}
void standingball::resizeDown() {
	stand->resizeDown();
	ball->resizeDown();
	resized--;
	if (rotated == 1)
	{
		standref = RefPoint;
		ballref = { standref.x + (stand->getwidth() / 2 + ball->getradius()) , standref.y };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
		stand->Rotate();
	}
	else if (rotated == 2)
	{

		standref = RefPoint;
		ballref = { standref.x  , standref.y + (stand->getheight() / 2 + ball->getradius()) };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);
	}
	else if (rotated == 3)
	{
		standref = RefPoint;
		ballref = { standref.x - (stand->getwidth() / 2 + ball->getradius()) , standref.y };


		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);

	}
	else if (rotated == 0)
	{
		standref = RefPoint;
		ballref = { standref.x  , standref.y - (stand->getheight() / 2 + ball->getradius()) };

		stand->setRefPoint(standref);
		ball->setRefPoint(ballref);

	}
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
	if (!flipped) {
		axis = RefPoint.x - hand1->getwidth() ;
		RefPoint.x -= 2 * (RefPoint.x - axis);
		faceref.x -= 2 * (faceref.x - axis);
		hand1ref.x -= 2 * (hand1ref.x - axis);
		hand2ref.x -= 2 * (hand2ref.x - axis);
		body->setAxis(axis);
		body->Flip();
		Leg1->setAxis(axis);
		Leg1->Flip();
		Leg2->setAxis(axis);
		Leg2->Flip();
		flipped = true;

	}
	else {
		axis = RefPoint.x + hand1->getwidth();
		RefPoint.x -= 2 * (RefPoint.x - axis);
		faceref.x -= 2 * (faceref.x - axis);
		hand1ref.x -= 2 * (hand1ref.x - axis);
		hand2ref.x -= 2 * (hand2ref.x - axis);
		body->setAxis(axis);
		body->Flip();
		Leg1->setAxis(axis);
		Leg1->Flip();
		Leg2->setAxis(axis);
		Leg2->Flip();
		flipped = false;
	}
		
	

}
void strawman::Rotate() {
	if (rotated == 0)
	{

		
		/*bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y + hand1->getheight() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y - hand1->getheight() / 2 };
		leg1ref = { RefPoint.x - (body->getheight()) / 2 , RefPoint.y + hand1->getheight() / 4 };
		leg2ref = { RefPoint.x - (body->getheight()) / 2, RefPoint.y - hand1->getheight() / 4 };
		faceref = { RefPoint.x + (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };*/

		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y + body->getbase() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y - body->getbase()/ 2 };
		leg1ref = { RefPoint.x - (body->getheight()) / 2 , RefPoint.y + body->getbase() / 4 };
		leg2ref = { RefPoint.x - (body->getheight()) / 2, RefPoint.y - body->getbase() / 4 };
		faceref = { RefPoint.x + (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };


		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Face->setRefPoint(faceref);

		body->setnrefr(bodyref);
		Leg1->setnrefr(leg1ref);
		Leg2->setnrefr(leg2ref);

		body->Rotate();
		hand1->Rotate();
		hand2->Rotate();
		Leg1->Rotate();
		Leg2->Rotate();
		Face->Rotate();




		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		body->setRefPoint(bodyref);
		rotated += 1;


	

	}
	else if (rotated == 1)
	{

		/*bodyref = RefPoint;
		hand1ref = { RefPoint.x - hand1->getheight() / 2, RefPoint.y };
		hand2ref = { RefPoint.x + hand1->getheight() / 2, RefPoint.y };
		leg1ref = { RefPoint.x - hand1->getheight() / 4, RefPoint.y - (body->getheight() / 2) };
		leg2ref = { RefPoint.x + hand1->getheight() / 4, RefPoint.y - (body->getheight()) / 2 };
		faceref = { RefPoint.x,RefPoint.y + (Face->getradius() + body->getheight()) / 2 };*/
		
		bodyref = RefPoint;
		hand1ref = { RefPoint.x - body->getbase() / 2, RefPoint.y };
		hand2ref = { RefPoint.x + body->getbase() / 2, RefPoint.y };
		leg1ref = { RefPoint.x - body->getbase() / 4, RefPoint.y - (body->getheight() / 2) };
		leg2ref = { RefPoint.x + body->getbase() / 4, RefPoint.y - (body->getheight() / 2 )};
		faceref = { RefPoint.x,RefPoint.y + (Face->getradius() + body->getheight()) / 2 };

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Face->setRefPoint(faceref);

		body->setnrefr(bodyref);
		Leg1->setnrefr(leg1ref);
		Leg2->setnrefr(leg2ref);
		
		body->Rotate();
		hand1->Rotate();
		hand2->Rotate();
		Leg1->Rotate();
		Leg2->Rotate();
		Face->Rotate();;


		rotated += 1;

		body->setRefPoint(bodyref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);

	}
	else if (rotated == 2)
	{

		/*bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y - hand1->getwidth() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y + hand1->getwidth() / 2 };
		leg1ref = { RefPoint.x + (body->getheight()) / 2 , RefPoint.y - hand1->getwidth() / 4 };
		leg2ref = { RefPoint.x + (body->getheight()) / 2, RefPoint.y + hand1->getwidth() / 4 };
		faceref = { RefPoint.x - (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };*/

		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y - body->getbase() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y + body->getbase() / 2 };
		leg1ref = { RefPoint.x + (body->getheight()) / 2 , RefPoint.y - body->getbase() / 4 };
		leg2ref = { RefPoint.x + (body->getheight()) / 2, RefPoint.y + body->getbase() / 4 };
		faceref = { RefPoint.x - (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };

		rotated += 1;

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Face->setRefPoint(faceref);

		body->setnrefr(bodyref);
		Leg1->setnrefr(leg1ref);
		Leg2->setnrefr(leg2ref);

		body->Rotate();
		hand1->Rotate();
		hand2->Rotate();
		Leg1->Rotate();
		Leg2->Rotate();
		Face->Rotate();
		
		body->setRefPoint(bodyref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);

	}
	else if (rotated == 3)
	{
		/*bodyref = RefPoint;
		hand1ref = { RefPoint.x + hand1->getheight() / 2, RefPoint.y };
		hand2ref = { RefPoint.x - hand1->getheight() / 2, RefPoint.y };
		leg1ref = { RefPoint.x + hand1->getheight() / 4, RefPoint.y + (body->getheight() / 2) };
		leg2ref = { RefPoint.x - hand1->getheight() / 4, RefPoint.y + (body->getheight()) / 2 };
		faceref = { RefPoint.x,RefPoint.y - (Face->getradius() + body->getheight()) / 2};*/

		bodyref = RefPoint;
		hand1ref = { RefPoint.x + body->getbase() / 2, RefPoint.y };
		hand2ref = { RefPoint.x - body->getbase() / 2, RefPoint.y };
		leg1ref = { RefPoint.x + body->getbase() / 4, RefPoint.y + (body->getheight() / 2) };
		leg2ref = { RefPoint.x - body->getbase() / 4, RefPoint.y + (body->getheight() / 2) };
		faceref = { RefPoint.x,RefPoint.y - (Face->getradius() + body->getheight()) / 2 };

		rotated = 0;

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Face->setRefPoint(faceref);

		body->setnrefr(bodyref);
		Leg1->setnrefr(leg1ref);
		Leg2->setnrefr(leg2ref);

		body->Rotate();
		hand1->Rotate();
		hand2->Rotate();
		Leg1->Rotate();
		Leg2->Rotate();
		Face->Rotate();

		body->setRefPoint(bodyref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);

	}

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

		if (newRef.y + (body->getheight()) < (config.windHeight - config.statusBarHeight)) {
			this->setRefPoint(newRef);
			hand1ref.y += config.gridSpacing;
			hand2ref.y += config.gridSpacing;
			faceref.y += config.gridSpacing;
			Leg1->move(key);
			Leg2->move(key);
			body->move(key);

		}
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - hand1->getwidth() > 0) {
			this->setRefPoint(newRef);
			hand1ref.x -= config.gridSpacing;
			hand2ref.x -= config.gridSpacing;
			faceref.x -= config.gridSpacing;
			Leg1->move(key);
			Leg2->move(key);
			body->move(key);

		}
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + hand1->getwidth() < config.windWidth) {
			this->setRefPoint(newRef);
			hand1ref.x += config.gridSpacing;
			hand2ref.x += config.gridSpacing;
			faceref.x += config.gridSpacing;
			Leg1->move(key);
			Leg2->move(key);
			body->move(key);
		}
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (Face->getradius() * 2 + body->getheight() / 2) > config.toolBarHeight) {
			this->setRefPoint(newRef);
			hand1ref.y -= config.gridSpacing;
			hand2ref.y -= config.gridSpacing;
			faceref.y -= config.gridSpacing;
			Leg1->move(key);
			Leg2->move(key);
			body->move(key);
		}
		break;

	}
}
void strawman::resizeUp() {
	body->resizeUp();
	hand1->resizeUp();
	hand2->resizeUp();
	Leg1->resizeUp();
	Leg2->resizeUp();
	Face->resizeUp();
	resized++;
	point newRef;
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };
		if (newRef.y + (body->getheight()) > (config.windHeight - config.statusBarHeight))
		{
			body->resizeDown();
			hand1->resizeDown();
			hand2->resizeDown();
			Leg1->resizeDown();
			Leg2->resizeDown();
			Face->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - hand1->getwidth() < 0)
		{
			body->resizeDown();
			hand1->resizeDown();
			hand2->resizeDown();
			Leg1->resizeDown();
			Leg2->resizeDown();
			Face->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + hand1->getwidth() > config.windWidth)
		{
			body->resizeDown();
			hand1->resizeDown();
			hand2->resizeDown();
			Leg1->resizeDown();
			Leg2->resizeDown();
			Face->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (Face->getradius() * 2 + body->getheight() / 2) < config.toolBarHeight)
		{
			body->resizeDown();
			hand1->resizeDown();
			hand2->resizeDown();
			Leg1->resizeDown();
			Leg2->resizeDown();
			Face->resizeDown();
			resized--;
		}

	if (rotated == 1)
	{
		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y + hand1->getwidth() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y - hand1->getwidth() / 2 };
		leg1ref = { RefPoint.x - (body->getheight()) / 2 , RefPoint.y + hand1->getwidth() / 4 };
		leg2ref = { RefPoint.x - (body->getheight()) / 2, RefPoint.y - hand1->getwidth() / 4 };
		faceref = { RefPoint.x + (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
	else if (rotated == 2)
	{
		bodyref = RefPoint;
		hand1ref = { RefPoint.x - hand1->getwidth() / 2, RefPoint.y };
		hand2ref = { RefPoint.x + hand1->getwidth() / 2, RefPoint.y };
		leg1ref = { RefPoint.x - hand1->getwidth() / 4, RefPoint.y - (body->getheight() / 2) };
		leg2ref = { RefPoint.x + hand1->getwidth() / 4, RefPoint.y - (body->getheight()) / 2 };
		faceref = { RefPoint.x,RefPoint.y + (Face->getradius() + body->getheight()) / 2 };

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
	else if (rotated == 3)
	{


		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y - hand1->getwidth() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y + hand1->getwidth() / 2 };
		leg1ref = { RefPoint.x + (body->getheight()) / 2 , RefPoint.y - hand1->getwidth() / 4 };
		leg2ref = { RefPoint.x + (body->getheight()) / 2, RefPoint.y + hand1->getwidth() / 4 };
		faceref = { RefPoint.x - (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
	else if (rotated == 0)
	{
		bodyref = RefPoint;
		hand1ref = { RefPoint.x + hand1->getwidth() / 2, RefPoint.y };
		hand2ref = { RefPoint.x - hand1->getwidth() / 2, RefPoint.y };
		leg1ref = { RefPoint.x + hand1->getwidth() / 4, RefPoint.y + (body->getheight() / 2) };
		leg2ref = { RefPoint.x - hand1->getwidth() / 4, RefPoint.y + (body->getheight()) / 2 };
		faceref = { RefPoint.x,RefPoint.y - (Face->getradius() + body->getheight()) / 2 };
		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
}
void strawman::resizeDown() {
	body->resizeDown();
	hand1->resizeDown();
	hand2->resizeDown();
	Leg1->resizeDown();
	Leg2->resizeDown();
	Face->resizeDown();
	resized--;
	if (rotated == 1)
	{
		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y + hand1->getwidth() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y - hand1->getwidth() / 2 };
		leg1ref = { RefPoint.x - (body->getheight()) / 2 , RefPoint.y + hand1->getwidth() / 4 };
		leg2ref = { RefPoint.x - (body->getheight()) / 2, RefPoint.y - hand1->getwidth() / 4 };
		faceref = { RefPoint.x + (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
	else if (rotated == 2)
	{
		bodyref = RefPoint;
		hand1ref = { RefPoint.x - hand1->getwidth() / 2, RefPoint.y };
		hand2ref = { RefPoint.x + hand1->getwidth() / 2, RefPoint.y };
		leg1ref = { RefPoint.x - hand1->getwidth() / 4, RefPoint.y - (body->getheight() / 2) };
		leg2ref = { RefPoint.x + hand1->getwidth() / 4, RefPoint.y - (body->getheight()) / 2 };
		faceref = { RefPoint.x,RefPoint.y + (Face->getradius() + body->getheight()) / 2 };

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
	else if (rotated == 3)
	{


		bodyref = RefPoint;
		hand1ref = { RefPoint.x , RefPoint.y - hand1->getwidth() / 2 };
		hand2ref = { RefPoint.x, RefPoint.y + hand1->getwidth() / 2 };
		leg1ref = { RefPoint.x + (body->getheight()) / 2 , RefPoint.y - hand1->getwidth() / 4 };
		leg2ref = { RefPoint.x + (body->getheight()) / 2, RefPoint.y + hand1->getwidth() / 4 };
		faceref = { RefPoint.x - (Face->getradius() + body->getheight()) / 2 ,RefPoint.y };

		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
	else if (rotated == 0)
	{
		bodyref = RefPoint;
		hand1ref = { RefPoint.x + hand1->getwidth() / 2, RefPoint.y };
		hand2ref = { RefPoint.x - hand1->getwidth() / 2, RefPoint.y };
		leg1ref = { RefPoint.x + hand1->getwidth() / 4, RefPoint.y + (body->getheight() / 2) };
		leg2ref = { RefPoint.x - hand1->getwidth() / 4, RefPoint.y + (body->getheight()) / 2 };
		faceref = { RefPoint.x,RefPoint.y - (Face->getradius() + body->getheight()) / 2 };
		hand1->setRefPoint(hand1ref);
		hand2->setRefPoint(hand2ref);
		Leg1->setRefPoint(leg1ref);
		Leg2->setRefPoint(leg2ref);
		Face->setRefPoint(faceref);
		body->setRefPoint(bodyref);
	}
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
	body->setRefPoint(bodyref);
	bullet1->setRefPoint(bullet1ref);
	bullet2->setRefPoint(bullet2ref);
	hand->setRefPoint(handref);
	body->draw();
	bullet1->draw();
	bullet2->draw();
	hand->draw();
	
}
void Gun::Flip() {
	if (!flipped) {
		axis = RefPoint.x - body->getwidth();
		RefPoint.x -= 2 * (RefPoint.x - axis);
		bullet1ref.x -= 2 * (bullet1ref.x - axis);
		bullet2ref.x -= 2 * (bullet2ref.x - axis);
		bodyref.x -= 2 * (bodyref.x - axis);
		hand->setAxis(axis);
		hand->Flip();
		flipped = true;

	}
	else {
		axis = RefPoint.x + body->getwidth();
		RefPoint.x -= 2 * (RefPoint.x - axis);
		bullet1ref.x -= 2 * (bullet1ref.x - axis);
		bullet2ref.x -= 2 * (bullet2ref.x - axis);
		bodyref.x -= 2 * (bodyref.x - axis);
		hand->setAxis(axis);
		hand->Flip();
		flipped = false;
	}
		
	

}
void Gun::Rotate() {

	if (rotated == 0)
	{


		bodyref = RefPoint;
		bullet1ref = { RefPoint.x , RefPoint.y + 6 * body->getwidth() / 5 };
		bullet2ref = { RefPoint.x , RefPoint.y + 3 * body->getwidth() / 2 };
		handref = { RefPoint.x - (hand->getbase() / 2 + body->getheight() / 2), RefPoint.y - (body->getwidth() / 2 - hand->getheight() / 2) };


		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setnrefr(handref);

		body->Rotate();
		hand->Rotate();

		rotated += 1;
		hand->setRefPoint(handref);


	}
	else if (rotated == 1)
	{

		bodyref = RefPoint;
		bullet1ref = { RefPoint.x - 6 * body->getheight() / 5, RefPoint.y };
		bullet2ref = { RefPoint.x - 3 * body->getheight() / 2, RefPoint.y };
		handref = { RefPoint.x + (body->getheight() / 2 - hand->getheight() / 2), RefPoint.y - (hand->getbase() / 2 + body->getwidth() / 2) };

		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setnrefr(handref);

		body->Rotate();
		hand->Rotate();

		rotated += 1;
		hand->setRefPoint(handref);



	}
	else if (rotated == 2)
	{

		bodyref = RefPoint;
		bullet1ref = { RefPoint.x , RefPoint.y - 6 * body->getwidth() / 5 };
		bullet2ref = { RefPoint.x , RefPoint.y - 3 * body->getwidth() / 2 };
		handref = { RefPoint.x + (hand->getbase() / 2 + body->getheight() / 2), RefPoint.y + (body->getwidth() / 2 - hand->getheight() / 2) };


		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setnrefr(handref);

		body->Rotate();
		hand->Rotate();

		hand->setRefPoint(handref);


		rotated += 1;




	}
	else if (rotated == 3)
	{
		bodyref = RefPoint;
		bullet1ref = { RefPoint.x + 6 * body->getheight() / 5, RefPoint.y };
		bullet2ref = { RefPoint.x + 3 * body->getheight() / 2, RefPoint.y };
		handref = { RefPoint.x - (body->getheight() / 2 - hand->getheight() / 2), RefPoint.y + (hand->getbase() / 2 + body->getwidth() / 2) };

		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setnrefr(handref);

		body->Rotate();
		hand->Rotate();

		hand->setRefPoint(handref);

		rotated = 0;

		

	}
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

		if (newRef.y + config.Gun.BodyWidth / 2 < (config.windHeight - config.statusBarHeight)) {
			this->setRefPoint(newRef);
			bodyref.y += config.gridSpacing;
			bullet1ref.y+= config.gridSpacing;
			bullet2ref.y += config.gridSpacing;
			hand->move(key);
		}
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - config.Gun.BodyLength / 2 > 0) {
			this->setRefPoint(newRef);
			bodyref.x -= config.gridSpacing;
			bullet1ref.x -= config.gridSpacing;
			bullet2ref.x -= config.gridSpacing;
			hand->move(key);
		
		}
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + 2 * config.Gun.BodyLength < config.windWidth) {
			this->setRefPoint(newRef);
			bodyref.x -= config.gridSpacing;
			bullet1ref.x -= config.gridSpacing;
			bullet2ref.x -= config.gridSpacing;
			hand->move(key);
		}
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - config.Gun.BodyWidth / 2 - config.Gun.GetHeight / 2 > config.toolBarHeight) {
			this->setRefPoint(newRef);
			bodyref.y -= config.gridSpacing;
			bullet1ref.y -= config.gridSpacing;
			bullet2ref.y -= config.gridSpacing;
			hand->move(key);
		
		}
		break;
	}

}
void Gun::resizeUp() {
	body->resizeUp();
	bullet1->resizeUp();
	bullet2->resizeUp();
	hand->resizeUp();
	resized++;
	point newRef;
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };

		if (newRef.y + body->getheight() / 2 > (config.windHeight - config.statusBarHeight)) {
			body->resizeDown();
			bullet1->resizeDown();
			bullet2->resizeDown();
			hand->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - body->getwidth() / 2 < 0) {
			body->resizeDown();
			bullet1->resizeDown();
			bullet2->resizeDown();
			hand->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + 2 * body->getwidth() > config.windWidth) {
			body->resizeDown();
			bullet1->resizeDown();
			bullet2->resizeDown();
			hand->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - body->getheight() / 2 - hand->getheight() / 2 < config.toolBarHeight) {
			body->resizeDown();
			bullet1->resizeDown();
			bullet2->resizeDown();
			hand->resizeDown();
			resized--;
		}
		if (rotated == 1)
		{
			bodyref = RefPoint;
			bullet1ref = { RefPoint.x , RefPoint.y + 6 * body->getwidth() / 5 };
			bullet2ref = { RefPoint.x , RefPoint.y + 3 * body->getwidth() / 2 };
			handref = { RefPoint.x - (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2), RefPoint.y - (body->getwidth() / 2 - config.Gun.GetHeight / 2) };


			body->setRefPoint(bodyref);
			bullet1->setRefPoint(bullet1ref);
			bullet2->setRefPoint(bullet2ref);
			hand->setRefPoint(handref);
		}
		else if (rotated == 2)
		{

			bodyref = RefPoint;
			bullet1ref = { RefPoint.x - 6 * body->getwidth() / 5, RefPoint.y };
			bullet2ref = { RefPoint.x - 3 * body->getwidth() / 2, RefPoint.y };
			handref = { RefPoint.x + (body->getwidth() / 2 - config.Gun.GetHeight / 2), RefPoint.y - (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2) };

			body->setRefPoint(bodyref);
			bullet1->setRefPoint(bullet1ref);
			bullet2->setRefPoint(bullet2ref);
			hand->setRefPoint(handref);

		}
		else if (rotated == 3)
		{

			bodyref = RefPoint;
			bullet1ref = { RefPoint.x , RefPoint.y - 6 * body->getwidth() / 5 };
			bullet2ref = { RefPoint.x , RefPoint.y - 3 * body->getwidth() / 2 };
			handref = { RefPoint.x + (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2), RefPoint.y + (body->getwidth() / 2 - config.Gun.GetHeight / 2) };


			body->setRefPoint(bodyref);
			bullet1->setRefPoint(bullet1ref);
			bullet2->setRefPoint(bullet2ref);
			hand->setRefPoint(handref);

		}
		else if (rotated == 0)
		{
			bodyref = RefPoint;
			bullet1ref = { RefPoint.x + 6 * body->getwidth() / 5, RefPoint.y };
			bullet2ref = { RefPoint.x + 3 * body->getwidth() / 2, RefPoint.y };
			handref = { RefPoint.x - (body->getwidth() / 2 - config.Gun.GetHeight / 2), RefPoint.y + (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2) };

			body->setRefPoint(bodyref);
			bullet1->setRefPoint(bullet1ref);
			bullet2->setRefPoint(bullet2ref);
			hand->setRefPoint(handref);

		}
}
void Gun::resizeDown() {
	body->resizeDown();
	bullet1->resizeDown();
	bullet2->resizeDown();
	hand->resizeDown();
	resized--;
	if (rotated == 1)
	{
		bodyref = RefPoint;
		bullet1ref = { RefPoint.x , RefPoint.y + 6 * body->getwidth() / 5 };
		bullet2ref = { RefPoint.x , RefPoint.y + 3 * body->getwidth() / 2 };
		handref = { RefPoint.x - (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2), RefPoint.y - (body->getwidth() / 2 - config.Gun.GetHeight / 2) };


		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);
	}
	else if (rotated == 2)
	{

		bodyref = RefPoint;
		bullet1ref = { RefPoint.x - 6 * body->getwidth() / 5, RefPoint.y };
		bullet2ref = { RefPoint.x - 3 * body->getwidth() / 2, RefPoint.y };
		handref = { RefPoint.x + (body->getwidth() / 2 - config.Gun.GetHeight / 2), RefPoint.y - (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2) };

		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);

	}
	else if (rotated == 3)
	{

		bodyref = RefPoint;
		bullet1ref = { RefPoint.x , RefPoint.y - 6 * body->getwidth() / 5 };
		bullet2ref = { RefPoint.x , RefPoint.y - 3 * body->getwidth() / 2 };
		handref = { RefPoint.x + (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2), RefPoint.y + (body->getwidth() / 2 - config.Gun.GetHeight / 2) };


		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);

	}
	else if (rotated == 0)
	{
		bodyref = RefPoint;
		bullet1ref = { RefPoint.x + 6 * body->getwidth() / 5, RefPoint.y };
		bullet2ref = { RefPoint.x + 3 * body->getwidth() / 2, RefPoint.y };
		handref = { RefPoint.x - (body->getwidth() / 2 - config.Gun.GetHeight / 2), RefPoint.y + (config.Gun.GetBase / 2 + config.Gun.BodyWidth / 2) };

		body->setRefPoint(bodyref);
		bullet1->setRefPoint(bullet1ref);
		bullet2->setRefPoint(bullet2ref);
		hand->setRefPoint(handref);

	}
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
	
	body->setRefPoint(bodyref);
	roof->setRefPoint(roofref);
	body->draw();
	roof->draw();

}
void house::Flip()
{

	if (!flipped) {
		axis = RefPoint.x - (body->getwidth() / 2);
		RefPoint.x -= 2 * (RefPoint.x - axis);
		bodyref.x -= 2 * (bodyref.x - axis);
		roof->setAxis(axis);
		roof->Flip();
		flipped = true;

	}
	else {
		axis = RefPoint.x + (body->getwidth() / 2);
		RefPoint.x -= 2 * (RefPoint.x - axis);
		bodyref.x -= 2 * (bodyref.x - axis);
		roof->setAxis(axis);
		roof->Flip();
		flipped = false;
	}
}
void house::Rotate() {

	if (rotated == 0)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x + (body->getwidth() + roof->getheight()) / 2 , RefPoint.y};

		rotated += 1;


		body->setRefPoint(bodyref);
		roof->setnrefr(roofref);

		body->Rotate();
		roof->Rotate();

		roof->setRefPoint(roofref);

	}
	else if (rotated == 1)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y + (body->getheight() + roof->getheight()) / 2};

		


		rotated += 1;


		body->setRefPoint(bodyref);
		roof->setnrefr(roofref);

		body->Rotate();
		roof->Rotate();
		roof->setRefPoint(roofref);


	}
	else if (rotated == 2)
	{
		bodyref = RefPoint;
		roofref = { RefPoint.x - (body->getwidth() + roof->getheight()) / 2, RefPoint.y};

		body->setRefPoint(bodyref);
		roof->setnrefr(roofref);

		body->Rotate();
		roof->Rotate();
		roof->setRefPoint(roofref);


		rotated += 1;


		

	}
	else if (rotated == 3)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y - (body->getheight() + roof->getheight()) / 2};

		body->setRefPoint(bodyref);
		roof->setnrefr(roofref);

		body->Rotate();
		roof->Rotate();

		roof->setRefPoint(roofref);

		rotated = 0;

	}
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

		if (newRef.y + body->getheight() / 2 < (config.windHeight - config.statusBarHeight)) {
			this->setRefPoint(newRef);

			bodyref.y += config.gridSpacing;
			roof->move(key);
		}
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - roof->getbase() / 2 > 0) {
			this->setRefPoint(newRef);
			bodyref.x -= config.gridSpacing;
			roof->move(key);
		}
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + roof->getbase() / 2 < config.windWidth) {
			this->setRefPoint(newRef);
			bodyref.x += config.gridSpacing;
			roof->move(key);
		}
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (body->getheight() + roof->getheight()) / 2 - 20 > config.toolBarHeight) {
			this->setRefPoint(newRef);
			bodyref.y -= config.gridSpacing;
			roof->move(key);
		}
		break;
	}

}
void house::resizeUp()
{
	body->resizeUp();		
	roof->dbah();
	resized++;

point newRef;
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };
if (newRef.y + body->getheight() / 2 > (config.windHeight - config.statusBarHeight)) {
	body->resizeDown();
	roof->resizeDown();
	resized--;
		}
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - roof->getbase() / 2 < 0) {
			body->resizeDown();
			roof->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + roof->getbase() / 2 > config.windWidth) {
			body->resizeDown();
			roof->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (body->getheight() + roof->getheight()) / 2 - 20 < config.toolBarHeight) {
			body->resizeDown();
			roof->resizeDown();
			resized--;
		}

	if (rotated == 1)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x + (body->getwidth() + roof->getheight()) / 2 , RefPoint.y };
		
		roof->setnrefr(roofref);
		roof->resizeUp();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);
	}
	else if (rotated == 2)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y + (body->getheight() + roof->getheight()) / 2 };

		roof->setnrefr(roofref);
		roof->resizeUp();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

	}
	else if (rotated == 3)
	{
		bodyref = RefPoint;
		roofref = { RefPoint.x - (body->getwidth() + roof->getheight()) / 2, RefPoint.y };
		
		roof->setnrefr(roofref);
		roof->resizeUp();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

	}
	else if (rotated == 0)
	{
		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y - (body->getheight() / 2 + roof->getheight() / 2) };
		
		roof->setnrefr(roofref);
		roof->resizeUp();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);
	}

	
}
void house::resizeDown()
{
	body->resizeDown();
	roof->hbah();
	resized--;
	if (rotated == 1)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x + (body->getheight() + roof->getheight()) / 2, RefPoint.y };
		
		roof->setnrefr(roofref);
		roof->resizeDown();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

	}
	else if (rotated == 2)
	{

		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y + (body->getheight() + roof->getheight()) / 2 };

		roof->setnrefr(roofref);
		roof->resizeDown();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

	}
	else if (rotated == 3)
	{
		bodyref = RefPoint;
		roofref = { RefPoint.x - (body->getheight() + roof->getheight()) / 2, RefPoint.y };

		roof->setnrefr(roofref);
		roof->resizeDown();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);

	}
	else if (rotated == 0)
	{
		bodyref = RefPoint;
		roofref = { RefPoint.x , RefPoint.y - (body->getheight() / 2 + roof->getheight() / 2) };

		roof->setnrefr(roofref);
		roof->resizeDown();

		body->setRefPoint(bodyref);
		roof->setRefPoint(roofref);
	}
	
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
		axis = RefPoint.x - (rec->getwidth() / 2);
		RefPoint.x -= 2 * (RefPoint.x - axis);
		circRef.x -= 2 * (circRef.x - axis);
		tri->setAxis(axis);
		tri->Flip();
		flipped = true;

	}
	else {
		axis = RefPoint.x + (rec->getwidth() / 2);
		RefPoint.x -= 2 * (RefPoint.x - axis);
		circRef.x -= 2 * (circRef.x - axis);
		tri->setAxis(axis);
		tri->Flip();
		flipped = false;
	}

	
	
}
void balance::Rotate() {


	if (rotated == 0)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x + (rec->getheight() / 2 + circ->getradius()) , RefPoint.y };
		triRef = { RefPoint.x - (tri->getheight() + rec->getheight()) / 2 , RefPoint.y};


		rotated += 1;
		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);

		tri->Rotate();
		rec->Rotate();
		circ->Rotate();

		tri->setRefPoint(triRef);


	}
	else if (rotated == 1)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x , RefPoint.y + (rec->getwidth() / 2 + circ->getradius()) };
		triRef = { RefPoint.x  , RefPoint.y - (tri->getheight() + rec->getwidth()) / 2 };

	

		rotated += 1;

		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);

		tri->Rotate();
		rec->Rotate();
		circ->Rotate();

		tri->setRefPoint(triRef);

	}
	else if (rotated == 2)
	{
		recRef = RefPoint;
		circRef = { RefPoint.x - (rec->getheight() / 2 + circ->getradius()) , RefPoint.y };
		triRef = { RefPoint.x + (tri->getheight() + rec->getheight()) / 2 , RefPoint.y};

	


		rotated += 1;


		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);

		tri->Rotate();
		rec->Rotate();
		circ->Rotate();

		tri->setRefPoint(triRef);


	}
	else if (rotated == 3)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x , RefPoint.y - (rec->getwidth() / 2 + circ->getradius()) };
		triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() + rec->getwidth()) / 2};

		

		rotated = 0;
		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);

		tri->Rotate();
		rec->Rotate();
		circ->Rotate();

		tri->setRefPoint(triRef);


	}
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

		if (newRef.y + (rec->getwidth() / 2 + tri->getheight()) < (config.windHeight - config.statusBarHeight)) {
			this->setRefPoint(newRef);
			circRef.y += config.gridSpacing;
			tri->move(key);
		}
		break;
	case 4:                      //Left arrow
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - rec->getwidth() / 2 > 0) {
			this->setRefPoint(newRef);
			circRef.x -= config.gridSpacing;
			tri->move(key);
		}
		break;
	case 6:                       //right arrow
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x +rec->getwidth()/2 < config.windWidth) {
			this->setRefPoint(newRef);
			circRef.x += config.gridSpacing;
			tri->move(key);
		}
		break;
	case 8:                      //Up arrow
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (rec->getwidth() / 2 + 2 * circ->getradius()) > config.toolBarHeight) {
			this->setRefPoint(newRef);
			circRef.y -= config.gridSpacing;
			tri->move(key);
		}
		break;
	}

}
void balance::resizeUp()
{
	rec->resizeUp();
	tri->resizeUp();
	circ->resizeUp();
	resized++;
	point newRef;
		newRef = { this->getRefPoint().x,this->getRefPoint().y + config.gridSpacing };
if (newRef.y + (rec->getwidth() / 2 + tri->getheight()) > (config.windHeight - config.statusBarHeight)) {
	rec->resizeDown();
	tri->resizeDown();
	circ->resizeDown();
	resized--;
		}
		newRef = { this->getRefPoint().x - config.gridSpacing,this->getRefPoint().y };
		if (newRef.x - rec->getwidth() / 2 < 0) {
			rec->resizeDown();
			tri->resizeDown();
			circ->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x + config.gridSpacing,this->getRefPoint().y };
		if (newRef.x + rec->getwidth() / 2 > config.windWidth) {
			rec->resizeDown();
			tri->resizeDown();
			circ->resizeDown();
			resized--;
		}
		newRef = { this->getRefPoint().x ,this->getRefPoint().y - config.gridSpacing };
		if (newRef.y - (rec->getwidth() / 2 + 2 * circ->getradius()) < config.toolBarHeight) {
			rec->resizeDown();
			tri->resizeDown();
			circ->resizeDown();
			resized--;
		}


		if (rotated == 1)
		{

			recRef = RefPoint;
			circRef = { RefPoint.x + (rec->getheight() / 2 + circ->getradius()) , RefPoint.y };
			triRef = { RefPoint.x - (tri->getheight() + rec->getheight()) / 2 , RefPoint.y };
			rec->setRefPoint(RefPoint);
			circ->setRefPoint(circRef);
			tri->setnrefr(triRef);


		}
		else if (rotated == 2)
		{

			recRef = RefPoint;
			circRef = { RefPoint.x , RefPoint.y + (rec->getwidth() / 2 + circ->getradius()) };
			triRef = { RefPoint.x  , RefPoint.y - (tri->getheight() + rec->getwidth()) / 2 };
			rec->setRefPoint(RefPoint);
			circ->setRefPoint(circRef);
			tri->setnrefr(triRef);
		}
		else if (rotated == 3)
		{
			recRef = RefPoint;
			circRef = { RefPoint.x - (rec->getheight() / 2 + circ->getradius()) , RefPoint.y };
			triRef = { RefPoint.x + (tri->getheight() + rec->getheight()) / 2 , RefPoint.y };


			rec->setRefPoint(RefPoint);
			circ->setRefPoint(circRef);
			tri->setnrefr(triRef);

		}
		else if (rotated == 0)
		{

			recRef = RefPoint;
			circRef = { RefPoint.x , RefPoint.y - (rec->getwidth() / 2 + circ->getradius()) };
			triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() + rec->getwidth()) / 2 };
			rec->setRefPoint(RefPoint);
			circ->setRefPoint(circRef);
			tri->setnrefr(triRef);

		}
}
void balance::resizeDown()
{
	rec->resizeDown();
	tri->resizeDown();
	circ->resizeDown();
	resized--;
	if (rotated == 1)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x + (rec->getheight() / 2 + circ->getradius()) , RefPoint.y };
		triRef = { RefPoint.x - (tri->getheight() + rec->getheight()) / 2 , RefPoint.y };
		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);


	}
	else if (rotated == 2)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x , RefPoint.y + (rec->getwidth() / 2 + circ->getradius()) };
		triRef = { RefPoint.x  , RefPoint.y - (tri->getheight() + rec->getwidth()) / 2 };
		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);
	}
	else if (rotated == 3)
	{
		recRef = RefPoint;
		circRef = { RefPoint.x - (rec->getheight() / 2 + circ->getradius()) , RefPoint.y };
		triRef = { RefPoint.x + (tri->getheight() + rec->getheight()) / 2 , RefPoint.y };


		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);

	}
	else if (rotated == 0)
	{

		recRef = RefPoint;
		circRef = { RefPoint.x , RefPoint.y - (rec->getwidth() / 2 + circ->getradius()) };
		triRef = { RefPoint.x  , RefPoint.y + (tri->getheight() + rec->getwidth()) / 2 };
		rec->setRefPoint(RefPoint);
		circ->setRefPoint(circRef);
		tri->setnrefr(triRef);

	}
}
