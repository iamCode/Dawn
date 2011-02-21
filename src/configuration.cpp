/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

    This file is a part of the dawn-rpg project <http://sourceforge.net/projects/dawn-rpg/>.

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

#include "configuration.h"

namespace Configuration
{
    void setResolution( uint16_t screenWidth, uint16_t screenHeight )
    {
        Configuration::screenWidth = screenWidth;
        Configuration::screenHeight = screenHeight;
    }

    void setBpp( uint8_t bpp )
    {
        Configuration::bpp = bpp;
    }

	void useFullscreen( bool fullscreenenabled )
    {
        Configuration::fullscreenenabled = fullscreenenabled;
    }

    void useSound( bool soundEnabled )
    {
        Configuration::soundenabled = soundenabled;
    }

    void showDebugStdout( bool debug_stdout )
    {
        Configuration::debug_stdout = debug_stdout;
    }

    void showDebugFileout( bool debug_fileout )
    {
        Configuration::debug_fileout = debug_fileout;
    }

    void showInfoMessages( bool show_info_messages )
    {
        Configuration::show_info_messages = show_info_messages;
    }

    void showWarningMessages( bool show_warn_messages )
    {
        Configuration::show_warn_messages = show_warn_messages;
    }

    uint16_t screenWidth = 1024;
    uint16_t screenHeight = 768;
    uint8_t bpp = 32;
    std::string logfile = "dawn-log.log"; // The logfile
    bool debug_stdout = false; // Write messages to stdout
    bool debug_fileout = false; // Write messages to a file
    bool show_info_messages = false; // Show or hide debug info
    bool show_warn_messages = false; // show or hide warnings
    bool fullscreenenabled = true;
    bool soundenabled = true;

}
