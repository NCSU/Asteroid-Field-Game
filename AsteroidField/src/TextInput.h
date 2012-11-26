/*
 * TextInput.h
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#ifndef TEXTINPUT_H_
#define TEXTINPUT_H_

#include "Text.h"

class TextInput : public Text {
private:
	string str;
public:
	TextInput();
	virtual ~TextInput();
	string getStr() const;
	void setStr(string);

	void handleInput(SDL_Event&);
};

#endif /* TEXTINPUT_H_ */
