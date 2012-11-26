/*
 * Object.h
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include "SDL/SDL.h"

#include <string>
using std::string;

class Object {
protected:
	SDL_Surface* obj;
	SDL_Surface* objOld;
	SDL_Rect objSrc;
	SDL_Rect objDst;
	SDL_Rect objOldDst;
	int xSpeed;
	int ySpeed;
public:
	Object();
	Object(string, int, int);
	virtual ~Object();
	void setSrcRect(int, int, int, int);
	void setDstRect(int, int);
	void setColorKey(int, int, int);
	void setSpeed(int, int);

	SDL_Rect getSrcRect() const;
	SDL_Rect getDstRect() const;
	int getXSpeed() const;
	int getYSpeed() const;

	void loadImage(string);
	void drawObject(SDL_Surface*, SDL_Surface*);
	void cleanObject(SDL_Surface*);
	double getDistance(int, int, int, int);
	virtual bool moveObject();
};

#endif /* OBJECT_H_ */
