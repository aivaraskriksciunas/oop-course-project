#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "CloseEventHandler.h"
#include "MouseEventHandler.h"
#include "KeyboardEventHandler.h"

class EventManager
{
public:

	void add_close_event_handler( CloseEventHandler* handler );
	void add_mouse_event_handler( MouseEventHandler* handler );
	void add_keyboard_event_handler( KeyboardEventHandler* handler );

	void poll_window_events( sf::RenderWindow* window );

	const sf::Vector2i* get_mouse_position();

private:
	std::vector<CloseEventHandler*> close_event_handlers;
	std::vector<MouseEventHandler*> mouse_event_handlers;
	std::vector<KeyboardEventHandler*> keyboard_event_handlers;

	sf::Vector2i mouse_position;
};

