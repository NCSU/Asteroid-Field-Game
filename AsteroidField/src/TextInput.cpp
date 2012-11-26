/*
 * TextInput.cpp
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include <string>
using std::string;

#include "TextInput.h"

TextInput::TextInput() : Text() {
	// TODO Auto-generated constructor stub
    str = "";
    SDL_EnableUNICODE(SDL_ENABLE);
}

string TextInput::getStr() const
{
    return str;
}

void TextInput::setStr(string str)
{
    this->str = str;
}

TextInput::~TextInput() {
	// TODO Auto-generated destructor stub
	TTF_CloseFont(textFont);
	SDL_FreeSurface(text);
	SDL_FreeSurface(textOld);
	SDL_EnableUNICODE(SDL_DISABLE);
}

void TextInput::handleInput(SDL_Event& event) {
	//If a key was pressed
	if( event.type == SDL_KEYDOWN ) {
		//Keep a copy of the current version of the string.
		string temp = str;
		//If the string less than maximum size.
		if(str.length() <= 7) {
			//If the key is a space.
			if( event.key.keysym.unicode == (Uint16)' ') {
				//Append the character.
				str += (char)event.key.keysym.unicode;
			}
			//If the key is a number.
			else if((event.key.keysym.unicode >= (Uint16)'0') && (event.key.keysym.unicode <= (Uint16)'9')) {
				//Append the character.
				str += (char)event.key.keysym.unicode;
			}
			//If the key is a uppercase letter.
			else if((event.key.keysym.unicode >= (Uint16)'A') && (event.key.keysym.unicode <= (Uint16)'Z')) {
				//Append the character.
				str += (char)event.key.keysym.unicode;
			}
			//If the key is a lowercase letter.
			else if((event.key.keysym.unicode >= (Uint16)'a') && (event.key.keysym.unicode <= (Uint16)'z')) {
				//Append the character.
				str += (char)event.key.keysym.unicode;
			}
			//If backspace was pressed and the string isn't blank.
			if((event.key.keysym.sym == SDLK_BACKSPACE) && (str.length() != 0)) {
				//Remove a character from the end.
				str.erase(str.length() - 1);
			}
			//If the string was changed.
			if(str != temp) {
				//Free the old surface.
				//SDL_FreeSurface( text );
				//Render a new text surface.
				text = TTF_RenderText_Solid(textFont, str.c_str(), textColor );
			}
		}
	}
}
