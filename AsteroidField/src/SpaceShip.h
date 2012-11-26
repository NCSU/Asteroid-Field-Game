/*
 * SpaceShip.h
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include "Object.h"
#include "Meteor.h"

class SpaceShip : public Object {
public:
	SpaceShip();
	SpaceShip(string, int, int);
	virtual ~SpaceShip();

	void handleInput(const bool*);
	bool moveObject();

	bool isColision(vector<Meteor*>& vec, SDL_Surface* screen);
};

#endif /* SPACESHIP_H_ */
