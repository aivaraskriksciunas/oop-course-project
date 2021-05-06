#pragma once

#include "Window.h"
#include "RenderQueue.h"
#include "World.h"
#include "CloseEventHandler.h"
#include "EventManager.h"
#include "UserInterface.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "LevelLoader.h"
#include "LevelManager.h"

class Game : public CloseEventHandler
{
public:

	Game();
	~Game();
	void start( Level& lvl, int window_width = 800, int window_height = 600 );

	bool on_close();

private:
	bool should_game_exit;

};

