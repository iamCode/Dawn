/**
    Copyright (C) 2009  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#ifndef __TIME_CONVERTER_HELPER__H_
#define __TIME_CONVERTER_HELPER__H_

#include <math.h>

namespace TimeConverter
{
    // display time based on current ticks and seconds
    inline std::string convertTime( uint32_t ticks, uint16_t duration )
    {
        // break our ticks down into hours, minutes or seconds and return a pretty string.
        std::string output_string;
        std::stringstream ss;
        std::string returnString;

        uint32_t thisDuration = SDL_GetTicks();
        uint16_t seconds = 0;
        uint16_t minutes = 0;
        uint16_t hours = 0;


        seconds = duration - floor( ( thisDuration - ticks ) / 1000 );
        hours = floor( (float)seconds / 3600 );
        minutes = ceil( (float)seconds / 60 ) - floor( (float)seconds / 3600 )*60;

        if ( minutes == 1 ) { minutes = 0; } // when we're below or at 60 seconds, dont display minutes.

        if ( hours > 0 )
        {
            ss << hours << "h ";
        }

        if ( minutes > 0 )
        {
            ss << minutes << "m ";
        }

        if ( minutes <= 0 && hours <= 0 )
        {
            ss << seconds << "s ";
        }

        output_string = ss.str();

        return output_string;
    }

    // display time based only on seconds, with full text format.
    inline std::string convertTime( uint16_t seconds )
    {
        // break our seconds down into hours, minutes or seconds and return a pretty string.
        std::string output_string;
        std::string returnString;
        std::stringstream ss;

        uint16_t minutes = 0;
        uint16_t hours = 0;


        hours = floor( (float)seconds / 3600 );
        minutes = ceil( (float)seconds / 60 ) - floor( (float)seconds / 3600 )*60;

        if ( minutes == 1 ) { minutes = 0; } // when we're below or at 60 seconds, dont display minutes.

        if ( hours > 0 )
        {
            if ( hours == 1 )
            {
                ss << hours << " hour ";
            } else {
                ss << hours << " hours ";
            }
        }

        if ( minutes > 0 )
        {
                ss << minutes << " minutes ";
        }

        if ( minutes <= 0 && hours <= 0 )
        {
            if ( seconds == 1 )
            {
                ss << seconds << " second";
            } else {
                ss << seconds << " seconds";
            }
        }

        output_string = ss.str();

        return output_string;
    }
}

#endif

