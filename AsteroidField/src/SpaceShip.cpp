/*
 * SpaceShip.cpp
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#include <vector>
using std::vector;

#include "SpaceShip.h"
#include "Object.h"
#include "Meteor.h"

const int SHIP_X = 300;
const int SHIP_Y = 400;

SpaceShip::SpaceShip() : Object() {
	// TODO Auto-generated constructor stub

}

SpaceShip::SpaceShip(string fileName, int xStartPos, int yStartPos) :
		Object(fileName, xStartPos, yStartPos) {
	// TODO Auto-generated constructor stub

}

SpaceShip::~SpaceShip() {
	// TODO Auto-generated destructor stub
	SDL_FreeSurface(obj);
	SDL_FreeSurface(objOld);
}

void SpaceShip::handleInput(const bool* keysHold) {
	if(keysHold[SDLK_LEFT]) {
	    if(!moveObject())
			setSpeed(0, 0);
		else
			setSpeed(-4, 0);
	}
	if(keysHold[SDLK_RIGHT]) {
		if(!moveObject())
			setSpeed(0, 0);
		else
			setSpeed(4, 0);
	}
	if(keysHold[SDLK_UP]) {
		if(!moveObject())
			setSpeed(0, 0);
		else
			setSpeed(0, -4);
	}
	if(keysHold[SDLK_DOWN]) {
		if(!moveObject())
			setSpeed(0, 0);
		else
			setSpeed(0, 4);
	}
}

bool SpaceShip::moveObject() {
	objDst.x += xSpeed;
	objDst.y += ySpeed;
	if(objDst.x <= 0) {
		xSpeed = 0;
		objDst.x++;
		return false;
	}
	if(objDst.x >= 640 - objDst.w) {
		xSpeed = 0;
		objDst.x--;
		return false;
	}
	if(objDst.y <= 0) {
		ySpeed = 0;
		objDst.y++;
		return false;
	}
	if(objDst.y >= 480 - objDst.h) {
		ySpeed = 0;
		objDst.y--;
		return false;
	}
	return true;
}

bool SpaceShip::isColision(vector<Meteor*>& vec, SDL_Surface* screen)
{
	for(unsigned i = 0; i < vec.size(); i++)
	{
		SDL_Rect shipDst = getDstRect();
		SDL_Rect vecDst = vec[i]->getDstRect();
		//Center positioning for SpaceShip coordinates.
		shipDst.x += shipDst.w/2;
		shipDst.y += shipDst.h/2;
		//Center positioning for Meteors coordinates.
		vecDst.x += vecDst.w/2;
		vecDst.y += vecDst.h/2;

	    if(getDistance(shipDst.x, shipDst.y, vecDst.x, vecDst.y) <= vecDst.h/2 + shipDst.w/2)
	    {
		    vec[i]->cleanObject(screen);
		    vec[i]->setDstRect(rand()%600, rand()%300);
		    vec[i]->setSpeed((rand()%6 - 3), (1 + rand()%5));

            setDstRect(SHIP_X, SHIP_Y);
		    return true;
		}
	}//End of for.
	return false;
}


