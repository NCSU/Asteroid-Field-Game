/*
 * Bullet.h
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Object.h"
#include "Meteor.h"

class Bullet : public Object {
public:
	Bullet();
	Bullet(string);
	virtual ~Bullet();

	bool moveObject();
    bool isColision(vector<Meteor*>&, SDL_Surface*);
};

#endif /* BULLET_H_ */
