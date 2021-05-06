#include "EventManager.h"

void EventManager::add_close_event_handler( CloseEventHandler* handler )
{
	close_event_handlers.push_back( handler );
}

void EventManager::add_keyboard_event_handler( KeyboardEventHandler* handler )
{
	keyboard_event_handlers.push_back( handler );
}

void EventManager::add_mouse_event_handler( MouseEventHandler* handler )
{
	mouse_event_handlers.push_back( handler );
}

const sf::Vector2i* EventManager::get_mouse_position()
{
	return &mouse_position;
}

void EventManager::poll_window_events( sf::RenderWindow* window )
{
	sf::Event ev;
	while ( window->pollEvent( ev ) )
	{
		if ( ev.type == sf::Event::Closed )
		{
			for ( CloseEventHandler* h : close_event_handlers )
				if ( h->on_close() ) break;
		}
		else if ( ev.type == sf::Event::MouseButtonReleased )
		{
			for ( MouseEventHandler* h : mouse_event_handlers )
				if ( h->on_mouse_up( ev.mouseButton.button, ev.mouseButton.x, ev.mouseButton.y ) ) break;
		}
		else if ( ev.type == sf::Event::MouseWheelScrolled )
		{
			for ( MouseEventHandler* h : mouse_event_handlers )
				if ( h->on_mouse_scroll( ev.mouseWheelScroll.delta, ev.mouseWheelScroll.x, ev.mouseWheelScroll.y ) ) break;
		}
		else if ( ev.type == sf::Event::KeyReleased )
		{
			for ( KeyboardEventHandler* h : keyboard_event_handlers )
				if ( h->on_key_up( ev.key ) ) break;
		}
	}

	// Store mouse position relative to window
	mouse_position = sf::Mouse::getPosition( *window );
}