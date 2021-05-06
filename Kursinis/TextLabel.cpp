#include "TextLabel.h"


TextLabel::TextLabel( sf::Vector2f pos, int char_size )
{
	label.setPosition( pos );	
	label.setFont( 
		*ServiceLocator::get_resource_manager()->get_font( F_MAIN_FONT ) );
	label.setCharacterSize( char_size );
	label.setFillColor( sf::Color::Black );
}

void TextLabel::draw( sf::RenderWindow* window )
{
	window->draw( label );
}

void TextLabel::update( const sf::Vector2i* mouse_pos )
{

}

void TextLabel::set_text( std::string txt )
{
	label.setString( txt );
}

std::string TextLabel::get_text()
{
	return label.getString();
}

void TextLabel::set_color( sf::Color color )
{
	label.setFillColor( color );
}