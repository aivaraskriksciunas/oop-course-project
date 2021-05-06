#include "ConnectionPoint.h"

int ConnectionPoint::IDENTIFIER_COUNTER = 0;

ConnectionPoint::ConnectionPoint( int rel_x, int rel_y, int g_x, int g_y, ConnectionPointType t )
	: type ( t )
{
	createShape( g_x + rel_x, g_y + rel_y, 10 );
}

ConnectionPoint::ConnectionPoint( int x, int y, ConnectionPointType t, double radius )
	: type ( t )
{
	createShape( x, y, radius );
}

void ConnectionPoint::createShape( int x, int y, double radius )
{
	shape = sf::CircleShape( radius );
	shape.setPosition( x, y );
	shape.setOrigin( radius, radius );
	shape.setFillColor( sf::Color::Black );

	// Assign an identifier to this point
	identifier = ConnectionPoint::IDENTIFIER_COUNTER++;
}

void ConnectionPoint::draw( sf::RenderWindow* window )
{
	window->draw( shape );
}

void ConnectionPoint::update( sf::Vector2f mouse_pos )
{
	if ( contains( mouse_pos ) )
		shape.setFillColor( sf::Color( 140, 140, 140 ) );
	else
		shape.setFillColor( fill_color );
}

bool ConnectionPoint::contains( sf::Vector2f& point )
{
	return shape.getGlobalBounds().contains( point.x, point.y );
}

sf::Vector2f ConnectionPoint::get_position()
{
	return shape.getPosition();
}

void ConnectionPoint::set_state( ElementStates state )
{
	this->state = state;
	if ( state == ElementStates::HIGH )
		fill_color = sf::Color( 200, 0, 0 );
	else if ( state == ElementStates::LOW )
		fill_color = sf::Color( 0, 0, 100 );
	else
		fill_color = sf::Color::Black;
}


bool ConnectionPoint::operator==( ConnectionPoint& cp )
{
	return identifier == cp.identifier;
}

bool ConnectionPoint::operator==( ConnectionPoint* cp )
{
	return identifier == cp->identifier;
}