/*
 * Meteor.h
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#ifndef METEOR_H_
#define METEOR_H_

#include "Object.h"

class Meteor : public Object {
private:
	bool isColiz;
public:
	Meteor();
	Meteor(string, int, int);
	virtual ~Meteor();

	bool isColision(vector<Meteor*>&);
	bool moveObject();
};

#endif /* METEOR_H_ */
