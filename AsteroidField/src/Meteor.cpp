/*
 * Meteor.cpp
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#include "SDL/SDL.h"

#include <vector>
using std::vector;

#include "Meteor.h"

//Meteor::Meteor() : Object() {
//	// TODO Auto-generated constructor stub

//}

Meteor::Meteor(string fileName, int xStartPos, int yStartPos) :
	Object(fileName, xStartPos, yStartPos) {
	// TODO Auto-generated constructor stub
    isColiz = false;
}

Meteor::~Meteor() {
	SDL_FreeSurface(obj);
	SDL_FreeSurface(objOld);
}

bool Meteor::moveObject() {
	objDst.x += xSpeed;
	objDst.y += ySpeed;
	if(objDst.x <= 0 || objDst.x >= 640 - objDst.w) {
		xSpeed = -xSpeed;
	}
	if(objDst.y <= 0 || objDst.y >= 480 - objDst.h) {
		ySpeed = -ySpeed;
	}
	return true;
}

bool Meteor::isColision(vector<Meteor*>& vec) {
	for(unsigned i = 0; i < vec.size(); i++) {
		SDL_Rect meteorDst = getDstRect();
		SDL_Rect vecDst = vec[i]->getDstRect();
		//Center positioning for main Meteor coordinates.
		meteorDst.x += meteorDst.w/2;
		meteorDst.y += meteorDst.h/2;
		//Center positioning for Meteors coordinates.
		vecDst.x += vecDst.w/2;
		vecDst.y += vecDst.h/2;

		if(getDistance(meteorDst.x, meteorDst.y, vecDst.x, vecDst.y) > (meteorDst.w/2 + vecDst.w/2)*2)
			isColiz = true;

	    if(getDistance(meteorDst.x, meteorDst.y, vecDst.x, vecDst.y) <= meteorDst.w/2 + vecDst.w/2 + 5) {
		    isColiz = false;
	    	setSpeed(-getXSpeed(), -getYSpeed());
		    vec[i]->setSpeed(-vec[i]->getXSpeed(), -vec[i]->getYSpeed());
		    return true;
		}
	}//End of for.
	return false;
}
