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

#include "ConfiguredFrames.h"

#include "ControlElement.h"
#include "configuration.h"
#include "fontcache.h"
#include "Player.h"
#include "globals.h"

#include "SDL/SDL.h"

extern SDL_Surface *screen;
extern std::auto_ptr<ConfigurableFrame> optionsFrame;
extern std::auto_ptr<ConfigurableFrame> mainMenuFrame;
extern std::auto_ptr<ConfigurableFrame> chooseClassFrame;

void deactivateCurrentGameLoopHandler();

class ToggleFrameFunction : public SimpleFunctionObject
{
	private:
		FramesBase *currentFrame;
		FramesBase *nextFrame;

	public:
		ToggleFrameFunction( FramesBase *current, FramesBase *next )
			: currentFrame( current ),
			  nextFrame( next )
		{
		}
		void operator() ()
		{
			currentFrame->toggle();
			nextFrame->toggle();
		}
};

class ToggleFullscreenFunction : public SimpleFunctionObject
{
	private:
		Label *fullscreenLabel;
		bool fullscreen;
	public:
		ToggleFullscreenFunction( Label *fullscreenLabel_, bool initialValue )
			: fullscreenLabel( fullscreenLabel_ ),
			  fullscreen( initialValue )
		{
		}
		void operator() ()
		{
			Configuration::fullscreenenabled = !Configuration::fullscreenenabled;
			if (Configuration::fullscreenenabled)
			{
				screen = SDL_SetVideoMode(Configuration::screenWidth,
										  Configuration::screenHeight, Configuration::bpp,
										  SDL_OPENGL | SDL_FULLSCREEN);
				if ( screen == NULL )
				{
					Configuration::fullscreenenabled = false;
					screen = SDL_SetVideoMode(Configuration::screenWidth,
											  Configuration::screenHeight, Configuration::bpp,
											  SDL_OPENGL);
				}
			}
			else
			{
				screen = SDL_SetVideoMode(Configuration::screenWidth,
										  Configuration::screenHeight, Configuration::bpp,
										  SDL_OPENGL);
				if ( screen == NULL )
				{
					Configuration::fullscreenenabled = true;
					screen = SDL_SetVideoMode(Configuration::screenWidth,
											  Configuration::screenHeight, Configuration::bpp,
											  SDL_OPENGL | SDL_FULLSCREEN);
				}
			}
			if ( Configuration::fullscreenenabled )
				fullscreenLabel->setText("Fullscreen");
			else
				fullscreenLabel->setText("Windowed");
		}
};

class QuitGameFunction : public SimpleFunctionObject
{
	void operator() ()
	{
		exit(0);
	}
};

class ChooseClassFunction : public SimpleFunctionObject
{
	private:
		CharacterClass::CharacterClass characterClass;
	public:
		ChooseClassFunction( CharacterClass::CharacterClass characterClass_ )
			: characterClass( characterClass_ )
		{
		}

		void operator() ()
		{
			// activate next handler
			Globals::getPlayer()->setClass( characterClass );
			deactivateCurrentGameLoopHandler();
		}
};

namespace ConfiguredFrames
{

void fillOptionsFrame( ConfigurableFrame *optionsFrame )
{
	optionsFrame->setAutoresize();
	optionsFrame->setCenteringLayout();
	optionsFrame->setCenterOnScreen();
	std::auto_ptr<Label> optionsFrameLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Select Options" ));
	optionsFrameLabel->setBaseColor( 1.0f, 0.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> optionsFrameBackLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Back" ));
	optionsFrameBackLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	optionsFrameBackLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> optionsFrameFullscreenLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Fullscreen" ));
	optionsFrameFullscreenLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	optionsFrameFullscreenLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	optionsFrame->setVisible( false );

	if ( ! Configuration::fullscreenenabled )
		optionsFrameFullscreenLabel->setText( "Windowed" );

	optionsFrameBackLabel->setOnClicked( new ToggleFrameFunction(optionsFrame, mainMenuFrame.get()) );
	optionsFrameFullscreenLabel->setOnClicked( new ToggleFullscreenFunction( optionsFrameFullscreenLabel.get(), Configuration::fullscreenenabled ) );

	optionsFrame->addChildFrame( 10, 0, std::auto_ptr<FramesBase>(optionsFrameBackLabel.release()) );
	optionsFrame->addChildFrame( 10, 22, std::auto_ptr<FramesBase>(optionsFrameFullscreenLabel.release()) );
	optionsFrame->addChildFrame( 0, 70, std::auto_ptr<FramesBase>(optionsFrameLabel.release()) );
}

void fillMainMenuFrame( ConfigurableFrame *mainMenuFrame )
{
	// setup main menu frame
	mainMenuFrame->setAutoresize();
	mainMenuFrame->setCenteringLayout();
	mainMenuFrame->setCenterOnScreen();
	std::auto_ptr<Label> quitLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Quit Game" ) );
	quitLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	quitLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> optionsLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Options" ) );
	optionsLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	optionsLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> newGameLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "New Game" ) );
	newGameLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	newGameLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );

	optionsLabel->setOnClicked( new ToggleFrameFunction( mainMenuFrame, optionsFrame.get() ) );
	newGameLabel->setOnClicked( new ToggleFrameFunction( mainMenuFrame, chooseClassFrame.get() ) );
	quitLabel->setOnClicked( new QuitGameFunction() );

	mainMenuFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(quitLabel.release()) );
	mainMenuFrame->addChildFrame( 0, 10, std::auto_ptr<FramesBase>(optionsLabel.release()) );
	mainMenuFrame->addChildFrame( 0, 30, std::auto_ptr<FramesBase>(newGameLabel.release()) );
}

void fillChooseClassFrame( ConfigurableFrame *chooseClassFrame )
{
	chooseClassFrame->setAutoresize();
	chooseClassFrame->setCenteringLayout();
	chooseClassFrame->setCenterOnScreen();
	std::auto_ptr<Label> captionLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Choose class" ) );
	captionLabel->setBaseColor( 1.0f, 0.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> licheLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Liche" ) );
	licheLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	licheLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> rangerLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Ranger" ) );
	rangerLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	rangerLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> warriorLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Warrior" ) );
	warriorLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	warriorLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> backLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Back" ) );
	backLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	backLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );

	licheLabel->setOnClicked( new ChooseClassFunction( CharacterClass::Liche ) );
	rangerLabel->setOnClicked( new ChooseClassFunction( CharacterClass::Ranger ) );
	warriorLabel->setOnClicked( new ChooseClassFunction( CharacterClass::Warrior ) );
	backLabel->setOnClicked( new ToggleFrameFunction( chooseClassFrame, mainMenuFrame.get() ) );

	chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(backLabel.release()) );
	chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(warriorLabel.release()) );
	chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(rangerLabel.release()) );
	chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(licheLabel.release()) );
	chooseClassFrame->addChildFrame( 0, 0, std::auto_ptr<FramesBase>(captionLabel.release()) );
}

} // namespace ConfiguredFrames

