#pragma once

#include "SFML/Graphics.hpp"

class KeyboardEventHandler
{
public:
	virtual bool on_key_down( sf::Event::KeyEvent ) { return false; }
	virtual bool on_key_up( sf::Event::KeyEvent ) { return false; }
};

