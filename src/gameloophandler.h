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

#ifndef GAMELOOPHANDLER_H
#define GAMELOOPHANDLER_H

#include <SDL/SDL_events.h>

class GameLoopHandler
{
public:
	virtual void activate( SDL_Event* lastEvent ) = 0;
	virtual void drawScene() = 0;
	virtual void handleEvents() = 0;
	virtual void updateScene() = 0;
	virtual void finish() = 0;
	void setDone();
	bool isDone();

protected:
	SDL_Event* lastEvent;
	bool finishMe;
};

class MainMenuHandler : public GameLoopHandler
{
public:
	virtual void activate( SDL_Event* lastEvent );
	virtual void drawScene();
	virtual void handleEvents();
	virtual void updateScene();
	virtual void finish();

private:
	bool mouseButtonDown;
};

class LoadingManager;
class LoadingScreen;

class LoadingScreenHandler : public GameLoopHandler
{
public:
	LoadingScreenHandler( LoadingScreen* loadingScreen, LoadingManager* loadingManager );
	virtual void activate( SDL_Event* lastEvent );
	virtual void drawScene();
	virtual void handleEvents();
	virtual void updateScene();
	virtual void finish();

	void setFollowHandler( GameLoopHandler* nextHandler );

private:
	LoadingManager* loadingManager;
	LoadingScreen* loadingScreen;
	uint32_t lastTicks;
	uint32_t curTicks;

	uint32_t drawingTime;
	uint32_t initStartTicks;

	GameLoopHandler* nextHandler;
};

class GameScreenHandler : public GameLoopHandler
{
public:
	virtual void activate( SDL_Event* lastEvent );
	virtual void drawScene();
	virtual void handleEvents();
	virtual void updateScene();
	virtual void finish();

private:
	uint32_t lastTicks;
	uint32_t curTicks;
	uint32_t ticksDiff;
};

#endif // GAMELOOPHANDLER_H
