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

#include "Frames.h"

#include "CTexture.h"
#include <memory>
#include "CDrawingHelpers.h"

/// FRAMES

namespace Frames
{
	std::auto_ptr<CTexture> frameTextures( NULL );

	void initFrameTextures()
	{
		if ( frameTextures.get() != NULL ) {
			return;
		}

		frameTextures = std::auto_ptr<CTexture>(new CTexture());
		frameTextures->LoadIMG( "data/interface/tooltip/lower_left2.tga", 0 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower_right2.tga", 1 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper_left2.tga", 2 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper_right2.tga", 3 );
		frameTextures->LoadIMG( "data/interface/tooltip/background2.tga", 4 );
		frameTextures->LoadIMG( "data/interface/tooltip/upper2.tga", 5 );
		frameTextures->LoadIMG( "data/interface/tooltip/lower2.tga", 6 );
		frameTextures->LoadIMG( "data/interface/tooltip/left2.tga", 7 );
		frameTextures->LoadIMG( "data/interface/tooltip/right2.tga", 8 );
	}

	void drawFrame( int leftX, int bottomY, int numBlocksX, int numBlocksY, int blockWidth, int blockHeight )
	{
		// draw the corners
		DrawingHelpers::mapTextureToRect( frameTextures->getTexture(0), leftX, blockWidth, bottomY, blockHeight); // lower left corner
		DrawingHelpers::mapTextureToRect( frameTextures->getTexture(1), leftX+blockWidth+(numBlocksX*blockWidth), blockWidth, bottomY, blockHeight); // lower right corner
		DrawingHelpers::mapTextureToRect( frameTextures->getTexture(2), leftX, blockWidth, bottomY+blockHeight+(numBlocksY*blockHeight), blockHeight); // upper left corner
		DrawingHelpers::mapTextureToRect( frameTextures->getTexture(3), leftX+blockWidth+(numBlocksX*blockWidth), blockWidth, bottomY+blockHeight+(numBlocksY*blockHeight), blockHeight); // upper right corner

		// draw the top and bottom borders
		for ( int blockX = 0; blockX < numBlocksX; blockX++ )
		{
			DrawingHelpers::mapTextureToRect( frameTextures->getTexture(5), leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY+blockHeight+(numBlocksY*blockHeight),blockHeight); // top border
			DrawingHelpers::mapTextureToRect( frameTextures->getTexture(6), leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY,blockHeight); // bottom border
		}

		// draw the right and left borders
		for ( int blockY = 0; blockY < numBlocksY; blockY++ )
		{
			DrawingHelpers::mapTextureToRect( frameTextures->getTexture(7), leftX,blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight); // left border
			DrawingHelpers::mapTextureToRect( frameTextures->getTexture(8), leftX+blockWidth+(numBlocksX*blockWidth),blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight); // right border
		}

		// draw the background
		for ( int blockY = 0; blockY < numBlocksY; blockY++ )
		{
			for ( int blockX = 0; blockX < numBlocksX; blockX++ )
			{
				DrawingHelpers::mapTextureToRect( frameTextures->getTexture(4), leftX+blockWidth+(blockX*blockWidth),blockWidth,bottomY+blockHeight+(blockY*blockHeight),blockHeight);
			}
		}
	}

	int calculateNeededBlockWidth( int contentWidth, int singleBlockWidth )
	{
		if ( contentWidth % singleBlockWidth == 0 )
			return (contentWidth / singleBlockWidth );
		else
			return (contentWidth / singleBlockWidth + 1 );
	}

	int calculateNeededBlockHeight( int contentHeight, int singleBlockHeight )
	{
		if ( contentHeight % singleBlockHeight == 0 )
			return (contentHeight / singleBlockHeight );
		else
			return (contentHeight / singleBlockHeight + 1 );
	}
} // namespace Frames

