#pragma once

#include <vector>
#include "Renderable.h"

class RenderQueue
{
public:
	int add_to_queue( Renderable* object );
	void remove_from_queue( int id );
	void draw( sf::RenderWindow* window );

private:

	std::vector<Renderable*> queue;

};

