#include "Button.h"

Button::Button( int posx, int posy, int event_code, int texture ):
	is_pressed( false ), 
	event_code( event_code )
{
	button_shape.setPosition( posx, posy );
	button_shape.setSize( sf::Vector2f( 40, 40 ));
	button_shape.setFillColor( sf::Color( 100, 100, 100, 140 ) );
	
	if ( texture != T_TOTAL )
	{
		icon.setPosition( posx, posy );
		icon.setSize( sf::Vector2f( 40, 40 ) );
		icon.setTexture( ServiceLocator::get_resource_manager()->get_texture( texture ) );
	}
}

void Button::draw( sf::RenderWindow* window )
{
	window->draw( button_shape );
	window->draw( icon );
}


void Button::update( const sf::Vector2i* mouse_pos )
{
	auto bounds = button_shape.getGlobalBounds();
	if ( bounds.contains( mouse_pos->x, mouse_pos->y ) )
	{
		// Remove transparency if user hovers mouse on button
		button_shape.setFillColor( sf::Color( 100, 100, 100, 255 ) );
	}
	else
	{
		button_shape.setFillColor( sf::Color( 100, 100, 100, 140 ) );
	}
}

bool Button::handle_click( int posx, int posy )
{
	auto bounds = button_shape.getGlobalBounds();
	
	if ( bounds.contains( posx, posy ) )
	{
		is_pressed = true;
		return true;
	}

	return false;
}

bool Button::poll_is_clicked()
{
	if ( is_pressed )
	{
		is_pressed = false;
		return true;
	}
	
	return false;
}