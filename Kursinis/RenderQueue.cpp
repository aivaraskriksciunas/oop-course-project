#include "RenderQueue.h"


int RenderQueue::add_to_queue( Renderable* object )
{
	int qsize = queue.size();

	queue.push_back( object );

	return qsize;
}

void RenderQueue::remove_from_queue( int id )
{
	queue.erase( queue.begin() + id );
}

void RenderQueue::draw( sf::RenderWindow* window )
{
	for ( auto& r : queue )
		r->draw( window );
}