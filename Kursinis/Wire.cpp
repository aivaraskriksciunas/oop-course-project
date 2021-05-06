#include "Wire.h"

Wire::Wire()
{
	set_fill_color( sf::Color::Black );
}

void Wire::draw( sf::RenderWindow* window )
{
	window->draw( p1 );
	window->draw( p2 );
	window->draw( p3 );
}

void Wire::update( sf::Vector2f& mouse_pos )
{
	// Adjust wire color based on voltage
	if ( output->get_state() == ElementStates::HIGH )
		set_fill_color( RED );
	else if ( output->get_state() == ElementStates::LOW )
		set_fill_color( BLUE );
	else
		set_fill_color( sf::Color::Black );

	// Send voltage through wire
	input->set_state( output->get_state() );
}

void Wire::set_fill_color( sf::Color color )
{
	p1.setFillColor( color );
	p2.setFillColor( color );
	p3.setFillColor( color );
}


void Wire::set_start_pos( sf::Vector2f pos )
{
	start_pos = pos;
}

void Wire::set_end_pos( sf::Vector2f pos )
{
	end_pos = pos;

	// x coord where the wire will split and go in y direction
	int lenx = pos.x - start_pos.x;
	int leny = pos.y - start_pos.y;

	int midpoint = lenx / 2;

	// Wire segment 1 ( first horizontal seg )
	p1.setPosition( start_pos );
	p1.setSize( sf::Vector2f( midpoint, WIRE_WIDTH ) );

	// Wire segment 2 ( vertical segment )
	p2.setPosition( sf::Vector2f(
		start_pos.x + midpoint,
		start_pos.y
	) );
	p2.setSize( sf::Vector2f(
		WIRE_WIDTH, leny
	) );

	// Wire segment 3 ( last horizontal seg )
	p3.setPosition( sf::Vector2f(
		start_pos.x + midpoint,
		start_pos.y + leny
	) );
	p3.setSize( sf::Vector2f(
		midpoint, WIRE_WIDTH
	) );
}

void Wire::set_input_element( ConnectionPoint* in )
{
	input = in;
}

void Wire::set_output_element( ConnectionPoint* out )
{
	output = out;
}

bool Wire::intersects( sf::Vector2f pos )
{
	return p1.getGlobalBounds().contains( pos ) ||
		p2.getGlobalBounds().contains( pos ) ||
		p3.getGlobalBounds().contains( pos );
}