#pragma once

#include "SFML/Graphics.hpp"
#include "ServiceLocator.h"

class Button
{
public:
	Button( int posx, int posy, int event_code = -1, int texture = T_TOTAL );

	void draw( sf::RenderWindow* window );

	void update( const sf::Vector2i* mouse_pos );
	
	bool handle_click( int posx, int posy );
	bool poll_is_clicked();

	int get_event_code() { return event_code;  }

private:
	sf::RectangleShape button_shape;
	sf::RectangleShape icon;

	bool is_pressed = false;
	int event_code = 0;
};

