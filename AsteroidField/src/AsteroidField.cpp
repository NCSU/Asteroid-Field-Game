//============================================================================
// Name        : AsteroidField.cpp
// Author      : BARAKOV
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

#include <time.h>
#include <vector>
#include <sstream>


using std::vector;

#include "Timer.h"
#include "Object.h"
#include "Meteor.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Text.h"
#include "TextInput.h"

//The frames per second
const int FRAMES_PER_SECOND = 20;

//The frame rate regulator
Timer fps;
//Timer for bonus
Timer tb;

const int W_WIDTH = 640;
const int W_HEIGHT = 480;
const char* W_TITLE = "Asteroid Field";

const int SHIP_X = 300;
const int SHIP_Y = 400;

static bool bonus = false;
static bool bonusState = false;

static int BULLET = 0;
static int ROCKET = 0;
static int SCORE = 0;
static int LIVES = 24;

vector<Meteor*> meteorVec;
vector<Meteor*> bonusVec;

vector<Bullet*> bulletVec;
vector<Bullet*> rocketVec;
vector<Bullet*> rocketVec2;
vector<Bullet*>::iterator it;

void Intro(SDL_Surface* s);

int main(int argc, char** args)
{
	srand(time(0));

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_WM_SetCaption(W_TITLE, 0);
	SDL_Surface* screen = SDL_SetVideoMode(W_WIDTH, W_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_Surface* bground = IMG_Load("bground.bmp");
	//Create new Text objects.
    Text* scoreTxt = new Text("Score: 0", 0, 0, {0, 255, 0}, 20);
    Text* livesTxt = new Text("Lives: 24", 520, 0, {0, 255, 0}, 20);
    Text* bulletTxt = new Text("Bullets: 199", 160, 0, {0, 255, 0}, 20);
    Text* rocketTxt = new Text("Rockets: 100", 320, 0, {0, 255, 0}, 20);
	Text* gameTxt = new Text("Game Over", 150, 220, {255, 0, 0}, 60);
	Text* msgTxt = new Text("Enter Name: ", 130, 120, {255, 0, 0}, 22);

	//Create new SpaceShip object.
    SpaceShip* objShip = new SpaceShip("rocket.bmp", SHIP_X, SHIP_Y);
    objShip->setColorKey(0, 0, 0);
    //Create new Meteor objects.
    meteorVec.push_back(new Meteor("meteor1.bmp", 50, rand()%300));
    meteorVec.push_back(new Meteor("meteor2.bmp", 100, rand()%300));
    meteorVec.push_back(new Meteor("meteor3.bmp", 150, rand()%300));
    meteorVec.push_back(new Meteor("meteor1.bmp", 200, rand()%300));
    meteorVec.push_back(new Meteor("meteor2.bmp", 250, rand()%300));
    meteorVec.push_back(new Meteor("meteor3.bmp", 300, rand()%300));

    //Create new Bullet objects.
    for(int i = 0; i < 200; i++) {
        bulletVec.push_back(new Bullet("bullet.bmp"));
    }
    for(int i = 0; i < 100; i++) {
        rocketVec.push_back(new Bullet("rckt.bmp"));
    }
    for(int i = 0; i < 100; i++) {
        rocketVec2.push_back(new Bullet("rckt.bmp"));
    }

    Intro(screen);

    //Start drawing the game.
    SDL_BlitSurface(bground, NULL, screen, NULL);
    for(unsigned i = 0; i < meteorVec.size(); i++) {
    	meteorVec[i]->setColorKey(255, 255, 255);
    	meteorVec[i]->setSpeed((rand()%8 - 4), (1 + rand()%5));
    	meteorVec[i]->drawObject(screen, bground);
    }

//    bonusVec.push_back(new Meteor("rBonus.bmp", 350, rand()%300));
//    for(unsigned i = 0; i < bonusVec.size(); i++) {
//   		bonusVec[i]->setColorKey(255, 0, 255);
//   		bonusVec[i]->setSpeed((rand()%8 - 4), (1 + rand()%5));
//   		bonusVec[i]->drawObject(screen, bground);
//   	}

//    Text* tt = new Text("TIME: 0", 100, 190, {255, 0, 0}, 22);
    //Start timer for bonuses
    tb.start();

    objShip->drawObject(screen, bground);
    scoreTxt->drawText(screen);
//    tt->drawText(screen);

    bulletTxt->drawText(screen);
    //rocketTxt->drawText(screen);
    livesTxt->drawText(screen);

	SDL_UpdateRect(screen, 0, 0, 0, 0);

	bool keysHold[323] = {false};
	SDL_Event event;

    //Start the game.
	while(true) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				break;
			}
			if(objShip->isColision(bonusVec,screen)){
				bonus=true;
				rocketTxt->drawText(screen);
			}

		    if(tb.getTicks()/1000 >= 10){
		    	tb.stop();
		    	bonusState=true;
		    	tb.start();
		    }
		    else if(tb.getTicks()/1000 < 10){bonusState=false;}

		    if(bonusState==true && bonus==false){

		    	bonusVec.push_back(new Meteor("rBonus.bmp", 350, rand()%300));
		        for(unsigned i = 0; i < bonusVec.size(); i++) {
		        	bonusVec[i]->setColorKey(255, 0, 255);
		        	bonusVec[i]->setSpeed((rand()%8 - 4), (1 + rand()%5));
		        	bonusVec[i]->drawObject(screen, bground);
		        }

		    }


			if(event.type == SDL_KEYDOWN) {
				keysHold[event.key.keysym.sym] = true;
				if(event.key.keysym.sym == SDLK_ESCAPE)
					break;
				if(event.key.keysym.sym == SDLK_SPACE) {

					if(BULLET < 199)
					{
						bulletVec[BULLET]->setSpeed(0, -8);
					    bulletVec[BULLET]->setDstRect(objShip->getDstRect().x+20, objShip->getDstRect().y-20);
					    bulletVec[BULLET]->setColorKey(0, 0, 0);
					    bulletVec[BULLET]->drawObject(screen, bground);
					    BULLET++;
					    bulletTxt->setTextRender("Bullets: ", 199-BULLET);
					}

					if(objShip->isColision(bonusVec,screen)){
						bonus=true;
						rocketTxt->drawText(screen);
					}
					if(ROCKET < 100 && bonus==true)
					{

						rocketVec[ROCKET]->setSpeed(0, -6);
						rocketVec[ROCKET]->setDstRect(objShip->getDstRect().x, objShip->getDstRect().y);
						rocketVec[ROCKET]->setColorKey(255, 0, 255);
						rocketVec[ROCKET]->drawObject(screen, bground);

						rocketVec2[ROCKET]->setSpeed(0, -6);
						rocketVec2[ROCKET]->setDstRect(objShip->getDstRect().x+40, objShip->getDstRect().y);
						rocketVec2[ROCKET]->setColorKey(255, 0, 255);
						rocketVec2[ROCKET]->drawObject(screen, bground);
					    ROCKET++;

					    if(ROCKET == 99){
					    	 for(int i = 0; i < ROCKET; i++){
					    		 rocketVec[i]->cleanObject(screen);
					    		 rocketVec2[i]->cleanObject(screen);
					    	 }
					    	bonus=false;
					    	ROCKET = 0;
					    	rocketTxt->cleanText(screen);

					    }
						rocketTxt->setTextRender("Rockets: ", 100-ROCKET);
					}
				}
			}
			if(event.type == SDL_KEYUP) {
				keysHold[event.key.keysym.sym] = false;

			}
		}
		//End of event processing.

		objShip->handleInput(keysHold);

        if(objShip->isColision(meteorVec, screen)){
        	livesTxt->setTextRender("Lives: ", --LIVES);
        }
        //Redraw Ship object.
        objShip->cleanObject(screen);
        objShip->drawObject(screen, bground);

        //Redraw Bullet objects.
        for(int i = 0; i < BULLET; i++) {
            if(!bulletVec[i]->moveObject()) {
                bulletVec[i]->cleanObject(screen);
            }
            else {
                if(bulletVec[i]->isColision(meteorVec, screen))
                {
                	scoreTxt->setTextRender("Score: ", SCORE += 10);
                }
                bulletVec[i]->cleanObject(screen);
                bulletVec[i]->drawObject(screen, bground);
            }
        }

        //Redraw Rocket objects.
           for(int i = 0; i < ROCKET; i++) {
               if(!rocketVec[i]->moveObject() || !rocketVec2[i]->moveObject()) {
            	   rocketVec[i]->cleanObject(screen);
            	   rocketVec2[i]->cleanObject(screen);
               }
               else {
                   if(rocketVec[i]->isColision(meteorVec, screen) || rocketVec2[i]->isColision(meteorVec, screen))
                   {
                   	scoreTxt->setTextRender("Score: ", SCORE += 10);
                   }
                   rocketVec[i]->cleanObject(screen);
                   rocketVec[i]->drawObject(screen, bground);
                   rocketVec2[i]->cleanObject(screen);
                   rocketVec2[i]->drawObject(screen, bground);
               }
           }

        //Redraw Meteor objects.
        for(unsigned i = 0; i < meteorVec.size(); i++) {
        	meteorVec[i]->moveObject();
        	meteorVec[i]->isColision(meteorVec);
        	meteorVec[i]->cleanObject(screen);
        	meteorVec[i]->drawObject(screen, bground);
        }

        //Redraw Bonus objects.
        for(unsigned i = 0; i < bonusVec.size(); i++) {
        	bonusVec[i]->moveObject();
        	bonusVec[i]->cleanObject(screen);
        	bonusVec[i]->drawObject(screen, bground);
        }

        //tt->setTextRender("TIME: ", tb.getTicks()/1000.f );
        //tt->setTextRender("TIME: ", startTime);

        //Redraw text fields.
        scoreTxt->cleanText(screen);
        scoreTxt->drawText(screen);
        bulletTxt->cleanText(screen);
        bulletTxt->drawText(screen);
        if(bonus==true){rocketTxt->cleanText(screen);
        rocketTxt->drawText(screen);}
        livesTxt->cleanText(screen);
        livesTxt->drawText(screen);
//      tt->cleanText(screen);
//      tt->drawText(screen);

		SDL_UpdateRect(screen, 0, 0, 0, 0);
		if(LIVES == 0) break; //If the game is over.

		if((fps.getTicks() < 1000/FRAMES_PER_SECOND)) {
		    //Sleep the remaining frame time
		    SDL_Delay((300 /FRAMES_PER_SECOND) - fps.getTicks());
		}


	} // End Game

	TextInput* name = new TextInput();
	name->setTextDst(270, 120, 100, 30);
	msgTxt->drawText(screen);
	while(true) {
	    if(SDL_PollEvent(&event)) {
	        name->handleInput(event);
	    	if((event.type == SDL_KEYDOWN ) && (event.key.keysym.sym == SDLK_RETURN)) {
	    		msgTxt->setTextDst(260, 190, 100, 30);
	    		msgTxt->setTextRender(name->getStr().append(" : "), SCORE);
	    		msgTxt->drawText(screen);
	    		break;
	    	}
	    }
	    name->drawText(screen);
	    SDL_UpdateRect(screen, 0, 0, 0, 0);
	}
	gameTxt->drawText(screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Delay(3000);

	//Cleanup.
	delete scoreTxt;
	delete bulletTxt;
	delete rocketTxt;
	delete livesTxt;
	delete gameTxt;
	delete msgTxt;
	delete name;
//	delete tt;
	delete objShip;

	for(unsigned i = 0; i < meteorVec.size(); i++) {
	        delete meteorVec[i];
	}
	for(unsigned i = 0; i < bonusVec.size(); i++) {
	        delete bonusVec[i];
	}

	for(unsigned i = 0; i < bulletVec.size(); i++) {
	        delete bulletVec[i];
    }
	for(unsigned i = 0; i < rocketVec.size(); i++) {
		    delete rocketVec[i];
	}
	for(unsigned i = 0; i < rocketVec2.size(); i++){
			delete rocketVec2[i];
	}

	SDL_FreeSurface(bground);
	SDL_FreeSurface(screen);
	SDL_Quit();

	return 0;
}//End of Main.

void Intro(SDL_Surface* s)
{
	SDL_Event event;
	SDL_Surface* bgr = IMG_Load("ast.bmp");
	SDL_BlitSurface(bgr, NULL, s, NULL);
	SDL_UpdateRect(s, 0, 0, 0, 0);

	while(true)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				break;
			}
			if(event.type == SDL_KEYDOWN)
			{
					SDL_FreeSurface(bgr);
					break;
			}
		}
	}
}



