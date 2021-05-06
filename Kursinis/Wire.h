#pragma once

#include "SFML/Graphics.hpp"
#include "ConnectionPoint.h"
#include "CircuitParams.h"

class Wire
{
public:
	Wire();

	void draw( sf::RenderWindow* window );
	void update( sf::Vector2f& mouse_pos );

	void set_start_pos( sf::Vector2f pos );
	void set_end_pos( sf::Vector2f pos );

	void set_input_element( ConnectionPoint* in );
	void set_output_element( ConnectionPoint* out );
	ConnectionPoint* get_input_element() { return input; }
	ConnectionPoint* get_output_element() { return output; }

	bool intersects( sf::Vector2f pos );

private:
	sf::RectangleShape p1;
	sf::RectangleShape p2;
	sf::RectangleShape p3;

	sf::Vector2f start_pos;
	sf::Vector2f end_pos;

	ConnectionPoint* input = nullptr;
	ConnectionPoint* output = nullptr;
	
	const int WIRE_WIDTH = 5;

	void set_fill_color( sf::Color color );
};

