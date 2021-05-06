#pragma once

#include "SFML/Graphics.hpp"
#include <thread>
#include "RenderQueue.h"

class Window
{
public:
	Window( int width = 800, int height = 600 );
	~Window();

	void start_render_thread();
	void stop_render_thread();
	RenderQueue* get_render_queue();
	sf::RenderWindow* get_window();

private:
	int width, height;
	
	sf::RenderWindow* window;
	std::thread render_thread;

	RenderQueue* render_queue;

	bool window_should_close = false;
	void render();

};

