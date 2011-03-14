#ifndef GAMELOOPHANDLER_H
#define GAMELOOPHANDLER_H

#include "SDL/SDL_events.h"

class GameLoopHandler
{
  public:
	virtual void activate( SDL_Event *lastEvent ) = 0;
	virtual void drawScene() = 0;
	virtual void handleEvents() = 0;
	virtual void updateScene() = 0;
	virtual void finish() = 0;
	void setDone();
	bool isDone();

  protected:
	SDL_Event *lastEvent;
	bool finishMe;
};

class MainMenuHandler : public GameLoopHandler
{
  public:
	virtual void activate( SDL_Event *lastEvent );
	virtual void drawScene();
	virtual void handleEvents();
	virtual void updateScene();
	virtual void finish();
	
  private:
	bool mouseButtonDown;
};

/*
class LoadingScreenHandler : public GameLoopHandler
{
  public:
	virtual void drawScene();
	virtual void handleEvents();
	virtual void updateScene();	
};

class GameScreenHandler : public GameLoopHandler
{
  public:
	virtual void drawScene();
	virtual void handleEvents();
	virtual void updateScene();	
};
*/

#endif // GAMELOOPHANDLER_H
