/* Copyright (C) 2009,2010,2011,2012  Dawn - 2D roleplaying game

   This file is a part of the dawn-rpg project <https://github.com/frusen/Dawn>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <stdio.h>
#include <stdarg.h>

#include "message.h"
#include "fontcache.h"

CMessage::CMessage()
{
  messageFont = NULL;
}

CMessage::~CMessage()
{
}

void CMessage::initFonts()
{
  messageFont = FontCache::getFontFromCache("data/verdana.ttf", 12);
}

void CMessage::DrawAll()
{
  for(unsigned int book = 0; book < MessageBook.size(); book++)
  {
    // if we have a lifetime, we need to wait until we start decaying the message.
    if(MessageBook[book].lifetime > 0.0)
    {
      MessageBook[book].startdecaythisframe = SDL_GetTicks();

      // currently waiting 1 second, until we decrease our lifetime with one second and then repeat.
      if((MessageBook[book].startdecaythisframe-MessageBook[book].startdecaylastframe) > 1000)
      {
	MessageBook[book].startdecaylastframe = MessageBook[book].startdecaythisframe;
	MessageBook[book].lifetime -= 1.0;
      }
    }

    // lifetime is up, lets start decaying...
    if(MessageBook[book].lifetime == 0.0)
    {
      MessageBook[book].thisframe = SDL_GetTicks();

      if((MessageBook[book].thisframe-MessageBook[book].lastframe) > MessageBook[book].decayrate)
      {
	MessageBook[book].lastframe = MessageBook[book].thisframe;
	MessageBook[book].transparency -= 0.01;
      }
    }

    // set the color + transparency then draw the text.
    glColor4f(MessageBook[book].red,MessageBook[book].green,MessageBook[book].blue,MessageBook[book].transparency);
    messageFont->drawText(MessageBook[book].x_pos,MessageBook[book].y_pos,MessageBook[book].string);
  }
  glColor4f(1.0f,1.0f,1.0f,1.0f);
}

void CMessage::AddText(int x, int y, float red, float green, float blue, float transparency, int decayrate, float lifetime, const char *text, ...)
{
  char buffer[1024];
  std::va_list args;

  // writing our text and arguments to the buffer
  va_start(args, text);
  vsnprintf(buffer,1024,text,args);
  va_end(args);

  // push everything to our vector.
  MessageBook.push_back(sBook(std::string(buffer), x, y, red, green, blue, transparency, decayrate, lifetime));
}

void CMessage::DeleteDecayed()
{
  for(unsigned int book = 0; book < MessageBook.size(); book++)
  {
    if(MessageBook[book].transparency < 0.0)
    {
      MessageBook.erase(MessageBook.begin()+book);
    }
  }
}
