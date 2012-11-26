/*
 * Bullet.cpp
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#include <vector>
using std::vector;

#include "Bullet.h"

Bullet::Bullet() : Object() {
	// TODO Auto-generated constructor stub

}

Bullet::Bullet(string fileName) :
		Object(fileName, 0, 0) {
	// TODO Auto-generated constructor stub

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
	SDL_FreeSurface(obj);
    SDL_FreeSurface(objOld);
}

bool Bullet::moveObject() {
	objDst.y += ySpeed;
	if(objDst.y <= 0) {
		ySpeed = 0;
		return false;
	}
	return true;
}

bool Bullet::isColision(vector<Meteor*>& vec, SDL_Surface* screen) {
	for(unsigned i = 0; i < vec.size(); i++) {
	    SDL_Rect bulletDst = getDstRect();
	    SDL_Rect vecDst = vec[i]->getDstRect();
	    //Center positioning for bullets X coordinates.
	    bulletDst.x += bulletDst.w/2;
	    //Center positioning for Meteors coordinates.
	    vecDst.x += vecDst.w/2;
	    vecDst.y += vecDst.h/2;

        if(getDistance(bulletDst.x, bulletDst.y, vecDst.x, vecDst.y) <= vecDst.h/2) {
	        vec[i]->cleanObject(screen);
	        vec[i]->setDstRect(rand()%600, rand()%300);
	        vec[i]->setSpeed((rand()%6 - 3), (1 + rand()%5));
	        return true;
	    }
    }//End of for.

	return false;
}
