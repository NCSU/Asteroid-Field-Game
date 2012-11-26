/*
 * Text.h
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#ifndef TEXT_H_
#define TEXT_H_

class Text {
protected:
	SDL_Surface* text;
	SDL_Surface* textOld;
	TTF_Font* textFont;
	SDL_Color textColor;
	SDL_Rect textDst;
public:
	Text();
	Text(string, int, int, SDL_Color, int);
	virtual ~Text();
    SDL_Rect getTextDst() const;

    void setTextColor(int, int, int);
    void setTextDst(int, int, int, int);
    void setTextRender(string);
    void setTextRender(string, int);

    void drawText(SDL_Surface*);
    void cleanText(SDL_Surface*);
};

#endif /* TEXT_H_ */
