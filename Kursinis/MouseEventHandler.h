#pragma once

#include "SFML/Graphics.hpp"

class MouseEventHandler
{
public:
	virtual bool on_mouse_down() { return false; }
	virtual bool on_mouse_up( int button, int x, int y ) { return false; }
	virtual bool on_mouse_scroll( float delta, int x, int y ) { return false; }
};

