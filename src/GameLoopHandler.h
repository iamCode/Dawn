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

class LoadingManager;
class LoadingScreen;

class LoadingScreenHandler : public GameLoopHandler
{
  public:
	LoadingScreenHandler( LoadingScreen *loadingScreen, LoadingManager *loadingManager );
	virtual void activate( SDL_Event *lastEvent );
	virtual void drawScene();
	virtual void handleEvents();
	virtual void updateScene();
	virtual void finish();

	void setFollowHandler( GameLoopHandler *nextHandler );
	
  private:
	LoadingManager *loadingManager;
	LoadingScreen *loadingScreen;
	uint32_t lastTicks;
	uint32_t curTicks;
	
	uint32_t drawingTime;
	uint32_t initStartTicks;
	
	GameLoopHandler *nextHandler;
};

class GameScreenHandler : public GameLoopHandler
{
  public:
	virtual void activate( SDL_Event *lastEvent );
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
