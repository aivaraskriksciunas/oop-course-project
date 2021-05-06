#pragma once

#include "SFML/Graphics.hpp"
#include "CircuitParams.h"

class ConnectionPoint
{
public:
	ConnectionPoint( int rel_x, int rel_y, int g_x, int g_y, ConnectionPointType type );
	ConnectionPoint( int x, int y, ConnectionPointType type, double radius = 10 );

	void draw( sf::RenderWindow* window );
	virtual void update( sf::Vector2f mouse_pos );

	bool contains( sf::Vector2f& point );

	sf::Vector2f get_position();

	// Set 'voltage'
	void set_state( ElementStates state );
	ElementStates get_state() { return state; }
	ConnectionPointType get_type() { return type; }

	// Utilities
	bool operator==( ConnectionPoint& cp );
	bool operator==( ConnectionPoint* cp );

private:
	static int IDENTIFIER_COUNTER;

	// Elements related to rendering
	void createShape( int posx, int posy, double radius );
	sf::Color fill_color = sf::Color::Black;
	sf::CircleShape shape;

	// Defines what voltage is running through this point
	ElementStates state = ElementStates::DEFAULT;

	// Define type
	ConnectionPointType type = ConnectionPointType::INPUT;

	bool is_output = false;
	int identifier = 0;
};

