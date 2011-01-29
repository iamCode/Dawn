/**
    Copyright (C) 2009,2010  Dawn - 2D roleplaying game

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

#include "utils.h"

#include "configuration.h"

#include "pnglite/pnglite.h"
#include "GLee/GLee.h"
#include <sstream>
#include <cstring>
#include <memory>

namespace DawnInterface {
    void addTextToLogWindow( GLfloat color[], const char *text, ... );
}

extern int world_x, world_y;

bool utils::file_exists(const std::string& file)
{
	std::ifstream temp(file.c_str());

	if(!temp)
		return false;
	return true;
}

void utils::takeScreenshot()
{
    int w = Configuration::screenWidth;
	int h = Configuration::screenHeight;

	png_t pngOutput;

	int screenshotIndex = 0;

	std::stringstream ss;

	ss << "screenshot" << screenshotIndex << ".png";
	std::string filename = ss.str();


    std::auto_ptr<unsigned char> outputImageAuto( new unsigned char[h*w*4] );
    unsigned char *outputImage = outputImageAuto.get();
    unsigned char *tempImage = outputImage;// Configuration::screenHeight*Configuration::screenWidth*4;

    glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE, outputImage);

	/* flip the pixel because opengl works from bottom left corner */
	for(int y = 0; y < h/2; y++)
	{
		memcpy(tempImage, outputImage+y*w*4, w*4);
		memcpy(outputImage+y*w*4, outputImage+(h-y-1)*w*4, w*4);
		memcpy(outputImage+(h-y-1)*w*4, tempImage,w*4);
	}

    // look for a free screenshot file to write to. screenshot0.PNG, screenshot1.PNG...screenshotX.PNG
    while ( utils::file_exists( filename ) )
    {
        screenshotIndex++;
        ss.str("");
        ss << "screenshot" << screenshotIndex << ".png";
        filename = ss.str();
    }

    if ( !filename.empty() )
    {
        png_init(0,0);
        png_open_file_write(&pngOutput,filename.c_str());

        png_set_data(&pngOutput, Configuration::screenWidth, Configuration::screenHeight, 8, PNG_TRUECOLOR_ALPHA, static_cast<unsigned char*>(outputImage));

        png_close_file(&pngOutput);

        float white[] = { 1.0f, 0.0f, 0.0f };
        DawnInterface::addTextToLogWindow( white, "Screenshot saved to %s.", filename.c_str() );
    }
}
