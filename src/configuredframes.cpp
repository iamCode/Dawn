/**
    Copyright (C) 2009,2010,2011  Dawn - 2D roleplaying game

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
    along with this program.  If not, see <http://www.gnu.org/licenses/>. **/

#include "configuredframes.h"

#include "controlelement.h"
#include "configuration.h"
#include "fontcache.h"
#include "player.h"
#include "globals.h"
#include "resolution.h"
#include "testinterface.h"
#include "SDL/SDL.h"
#include <sstream>

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

class ResolutionSelectionFunction : public SelectionBox::CallbackType
{
  private:
	std::vector<Resolution> resolutions;

  public:
	void setResolutions( std::vector<Resolution> resolutions )
	{
		this->resolutions = resolutions;
	}

	virtual void operator()( int selected )
	{
		assert( selected >= 0 && selected < resolutions.size() );
		uint16_t saveScreenWidth = Configuration::screenWidth;
		uint16_t saveScreenHeight = Configuration::screenHeight;
		uint8_t saveBpp = Configuration::bpp;
		bool saveFullscreen = Configuration::fullscreenenabled;

		Resolution setRes = resolutions[selected];
		Configuration::screenWidth = setRes.width;
		Configuration::screenHeight = setRes.height;
		Configuration::bpp = setRes.bpp;
		Configuration::fullscreenenabled = setRes.fullscreen;

		// write new configuration so it will take effect on next start
		Configuration::writeConfigurationToFile();

		Configuration::screenWidth = saveScreenWidth;
		Configuration::screenHeight = saveScreenHeight;
		Configuration::bpp = saveBpp;
		Configuration::fullscreenenabled = saveFullscreen;
	}
};

class QuitGameFunction : public SimpleFunctionObject
{
	void operator() ()
	{
		exit( 0 );
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
	//optionsFrame->setCenteringLayout();
	optionsFrame->setCenterOnScreen();
	std::auto_ptr<Label> optionsFrameLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Select Options" ));
	optionsFrameLabel->setBaseColor( 1.0f, 0.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> optionsFrameBackLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Back" ));
	optionsFrameBackLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	optionsFrameBackLabel->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	std::auto_ptr<Label> optionsFrameResolutionLabel( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), "Resolution:" ));
	optionsFrameResolutionLabel->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	std::auto_ptr<Label> optionsFrameWarningLabel0( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 12 ), "Note:" ));
	optionsFrameWarningLabel0->setBaseColor( 0.9f, 0.5f, 0.1f, 1.0f );
	std::auto_ptr<Label> optionsFrameWarningLabel1( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 12 ), "Changes in graphics options take place" ));
	optionsFrameWarningLabel1->setBaseColor( 0.9f, 0.5f, 0.1f, 1.0f );
	std::auto_ptr<Label> optionsFrameWarningLabel2( new Label( FontCache::getFontFromCache( "data/verdana.ttf", 12 ), "only after restarting Dawn" ));
	optionsFrameWarningLabel2->setBaseColor( 0.9f, 0.5f, 0.1f, 1.0f );

	std::auto_ptr<SelectionBox> optionsFrameResolutionSelection( new SelectionBox( FontCache::getFontFromCache( "data/verdana.ttf", 20 ), FontCache::getFontFromCache( "data/verdana.ttf", 10 ) ) );
	optionsFrameResolutionSelection->setBaseColor( 1.0f, 1.0f, 1.0f, 1.0f );
	optionsFrameResolutionSelection->setSelectColor( 1.0f, 1.0f, 0.0f, 1.0f );
	optionsFrame->setVisible( false );
	optionsFrameBackLabel->setOnClicked( new ToggleFrameFunction(optionsFrame, mainMenuFrame.get()) );
	std::vector<Resolution> possibleResolutions = Resolution::getPossibleResolutions();
	std::vector<std::string> resTexts;
	int selected = -1;
	for ( size_t curResNr=0; curResNr<possibleResolutions.size(); ++curResNr ) {
		Resolution &curRes = possibleResolutions[ curResNr ];
		std::ostringstream oss;
		oss << curRes.width << "x" << curRes.height << " ";
		if ( curRes.fullscreen ) {
			oss << "F";
		} else {
			oss << "W";
		}
		resTexts.push_back( oss.str() );

		if ( curRes.width == Configuration::screenWidth && curRes.height == Configuration::screenHeight
		     && curRes.bpp == Configuration::bpp && curRes.fullscreen == Configuration::fullscreenenabled ) {
			selected = curResNr;
		}
		dawn_debug_info( "possible resolution: %s", oss.str().c_str() );
	}

	optionsFrameResolutionSelection->setEntries( resTexts, selected );
	std::auto_ptr<ResolutionSelectionFunction> resolutionSelectionFunction( new ResolutionSelectionFunction() );
	resolutionSelectionFunction->setResolutions( possibleResolutions );
	optionsFrameResolutionSelection->setOnSelected( resolutionSelectionFunction.release() );

	optionsFrame->addChildFrame( 0, 10+optionsFrameBackLabel->getHeight() + 20+optionsFrameResolutionSelection->getHeight()+20+optionsFrameWarningLabel2->getHeight()+optionsFrameWarningLabel1->getHeight()+optionsFrameWarningLabel0->getHeight()+20, std::auto_ptr<FramesBase>(optionsFrameLabel.release()) );
	optionsFrame->addChildFrame( 0, 10+optionsFrameBackLabel->getHeight() + 20+optionsFrameResolutionSelection->getHeight()+20+optionsFrameWarningLabel2->getHeight()+optionsFrameWarningLabel1->getHeight(), std::auto_ptr<FramesBase>(optionsFrameWarningLabel0.release()) );
	optionsFrame->addChildFrame( 0, 10+optionsFrameBackLabel->getHeight() + 20+optionsFrameResolutionSelection->getHeight()+20+optionsFrameWarningLabel2->getHeight(), std::auto_ptr<FramesBase>(optionsFrameWarningLabel1.release()) );
	optionsFrame->addChildFrame( 0, 10+optionsFrameBackLabel->getHeight() + 20+optionsFrameResolutionSelection->getHeight()+20, std::auto_ptr<FramesBase>(optionsFrameWarningLabel2.release()) );
	optionsFrame->addChildFrame( 10 + optionsFrameResolutionLabel->getWidth() + 10, 10 + optionsFrameBackLabel->getHeight() + 20, std::auto_ptr<FramesBase>(optionsFrameResolutionSelection.release()) );
	optionsFrame->addChildFrame( 10, 10 + optionsFrameBackLabel->getHeight() + 20, std::auto_ptr<FramesBase>(optionsFrameResolutionLabel.release()) );
	optionsFrame->addChildFrame( 10, 10, std::auto_ptr<FramesBase>(optionsFrameBackLabel.release()) );
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

    #ifdef TESTINTERFACE  // if we compile with the testinterface, we need to export the newgame and options menu labels.
        TestInterface::publishChooseClass( newGameLabel.get() );
        TestInterface::publishOptions( optionsLabel.get() );
    #endif

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

