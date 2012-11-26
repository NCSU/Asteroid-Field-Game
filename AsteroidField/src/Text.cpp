/*
 * Text.cpp
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include <string>
using std::string;

#include "Text.h"

char* itoa(int value, char *string, int radix) {
  char tmp[33];
  char *tp = tmp;
  int i;
  unsigned v;
  int sign;
  char *sp;

  if (radix > 36 || radix <= 1) {
    //__set_errno(EDOM);
    return 0;
  }

  sign = (radix == 10 && value < 0);
  if (sign)
    v = -value;
  else
    v = (unsigned)value;
  while (v || tp == tmp) {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  if (string == 0)
    string = (char *)malloc((tp-tmp)+sign+1);
  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;
  return string;
}

Text::Text() {
	// TODO Auto-generated constructor stub
    text = NULL;
    textOld = SDL_LoadBMP("white.bmp");;
    textFont = TTF_OpenFont("c:\\Windows\\Fonts\\ARIAL.ttf", 20);
    textColor = {255, 255, 255};
    textDst = {0, 0, 0, 0};
}

Text::Text(string txt, int xPos, int yPos, SDL_Color aColor, int size) {
	// TODO Auto-generated constructor stub
	textFont = TTF_OpenFont("c:\\Windows\\Fonts\\ARIAL.ttf", size);
	textColor = aColor;
	text = TTF_RenderText_Blended(textFont, txt.c_str(), textColor);
	textOld = SDL_LoadBMP("white.bmp");
	textDst = {xPos, yPos, 130, 30};
}

SDL_Rect Text::getTextDst() const
{
    return textDst;
}

void Text::setTextDst(int aX, int aY, int aW, int aH)
{
    textDst = {aX, aY, aW, aH};
}

void Text::setTextColor(int aRed, int aGreen, int aBlue)
{
    textColor = {aRed, aGreen, aBlue};
}

Text::~Text() {
	// TODO Auto-generated destructor stub
	TTF_CloseFont(textFont);
	SDL_FreeSurface(text);
    SDL_FreeSurface(textOld);
}

void Text::setTextRender(string txt) {
	text = TTF_RenderText_Blended(textFont, txt.c_str(), textColor);
}

void Text::setTextRender(string txt, int count) {
	char temp[20];
	itoa(count, temp, 10);
	txt.append(temp);
	text = TTF_RenderText_Blended(textFont, txt.c_str(), textColor);
}

void Text::drawText(SDL_Surface* screen) {
	if(text != NULL) {
		SDL_BlitSurface(screen, &textDst, textOld, NULL);
	    SDL_BlitSurface(text, NULL, screen, &textDst);
	}
}

void Text::cleanText(SDL_Surface* screen) {
	if(textOld != NULL) {
        SDL_BlitSurface(textOld, NULL, screen, &textDst);
	}
}
