/*
 * Object.cpp
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#include "Object.h"

#include "SDL/SDL_image.h"
#include <math.h>




 Object::Object() {
	// TODO Auto-generated constructor stub
	obj = NULL;
	objOld = NULL;

	objSrc = {0, 0, 0, 0};
	objDst = { 0, 0, 0, 0};

	xSpeed = 0;
	ySpeed = 0;
}

 Object::Object(string fileName, int xStartPos, int yStartPos) {
	// TODO Auto-generated constructor stub
	obj = IMG_Load(fileName.c_str());
	objOld = IMG_Load(fileName.c_str());

	objSrc = { 0, 0, obj->w, obj->h};
	objDst = { xStartPos, yStartPos, obj->w, obj->h};

	xSpeed = 0;
	ySpeed = 0;
}

Object::~Object() {
	// TODO Auto-generated destructor stub
    SDL_FreeSurface(obj);
    SDL_FreeSurface(objOld);
}

void Object::setSrcRect(int aX, int aY, int aW, int aH) {
	objSrc.x = aX;
	objSrc.y = aY;
	objSrc.w = aW;
	objSrc.h = aH;
}

void Object::setDstRect(int aX, int aY) {
	objDst.x = aX;
	objDst.y = aY;
	objDst.w = obj->w;
	objDst.h = obj->h;
}

void Object::setColorKey(int aRed, int aGreen, int aBlue) {
	if(obj != NULL) {
		SDL_SetColorKey(obj, SDL_SRCCOLORKEY, SDL_MapRGB(obj->format, aRed, aGreen, aBlue));
	}
}

void Object::setSpeed(int aXSpeed, int aYSpeed) {
	ySpeed = aYSpeed;
	xSpeed = aXSpeed;
}

void Object::loadImage(string fileName) {
	obj = IMG_Load(fileName.c_str());
	objOld = IMG_Load(fileName.c_str());
}

//Getters
SDL_Rect Object::getSrcRect() const {
	return objSrc;
}

SDL_Rect Object::getDstRect() const {
	return objDst;
}

int Object::getXSpeed() const {
	return xSpeed;
}

int Object::getYSpeed() const {
	return ySpeed;
}

void Object::drawObject(SDL_Surface* screen, SDL_Surface* bground) {
	if(obj != NULL) {
		objOldDst = objDst;
		SDL_BlitSurface(bground, &objDst, objOld, NULL);
        SDL_BlitSurface(obj, NULL, screen, &objDst);
	}
}

void Object::cleanObject(SDL_Surface* screen) {
	if(objOld != NULL) {
	    SDL_BlitSurface(objOld, NULL, screen, &objOldDst);
	}
}

double Object::getDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool Object::moveObject() {
	return true;
}
