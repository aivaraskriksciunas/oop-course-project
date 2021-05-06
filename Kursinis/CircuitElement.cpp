#include "CircuitElement.h"

CircuitElement::~CircuitElement()
{}


void CircuitElement::deregister( Circuit* circuit )
{
	for ( ConnectionPoint& cp : connection_points )
		circuit->deregister_connection_point( &cp );
}

void CircuitElement::update( sf::Vector2f mouse_pos )
{
	for ( int i = 0; i < connection_points.size(); i++ )
	{
		connection_points[i].update( mouse_pos );
	}
}

void CircuitElement::draw( sf::RenderWindow* window )
{
	window->draw( shape );

	for ( ConnectionPoint& cp : connection_points )
		cp.draw( window );
}

void CircuitElement::register_connection_points( Circuit* circuit )
{
	for ( int i = 0; i < connection_points.size(); i++ )
	{
		circuit->register_connection_point( &connection_points[i] );
	}
}

bool CircuitElement::intersects( sf::Vector2f pos )
{
	return shape.getGlobalBounds().contains( pos );
}