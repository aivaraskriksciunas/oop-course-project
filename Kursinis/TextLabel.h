#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "ServiceLocator.h"
#include "ResourceManager.h"

class TextLabel
{
public:
	TextLabel( sf::Vector2f pos, int char_size = 30 );

	void draw( sf::RenderWindow* window );
	void update( const sf::Vector2i* mouse_pos );

	void set_text( std::string txt );
	std::string get_text();
	void set_color( sf::Color );

private:
	sf::Text label;
};

