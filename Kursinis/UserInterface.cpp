#include "UserInterface.h"

UserInterface::UserInterface( int w_width, int w_height )
	: w_width( w_width ), w_height( w_height ), 
	last_event( UI_EVENT_NONE )
{}

void UserInterface::create_buttons( Level& lvl )
{
	int y = 20;
	if ( lvl.available_gates[CircuitElementType::AND_GATE] )
	{
		buttons.push_back(
			new Button( w_width - 60, y, BTN_ADD_AND_GATE, T_ICON_AND ) );
		y += BTN_SPACING;
	}
	if ( lvl.available_gates[CircuitElementType::OR_GATE] )
	{
		buttons.push_back(
			new Button( w_width - 60, y, BTN_ADD_OR_GATE, T_ICON_OR ) );
		y += BTN_SPACING;
	}
	if ( lvl.available_gates[CircuitElementType::XOR_GATE] )
	{
		buttons.push_back(
			new Button( w_width - 60, y, BTN_ADD_XOR_GATE, T_ICON_XOR ) );
		y += BTN_SPACING;
	}
	if ( lvl.available_gates[CircuitElementType::NOT_GATE] )
	{
		buttons.push_back(
			new Button( w_width - 60, y, BTN_ADD_NOT_GATE, T_ICON_NOT ) );
		y += BTN_SPACING;
	}
	buttons.push_back(
		new Button( w_width - 60, y, BTN_START_SIMULATION, T_ICON_PLAY ) );
}

UserInterface::~UserInterface()
{
	// Free memory
	for ( int i = 0; i < buttons.size(); i++ )
		delete buttons[i];
	for ( int i = 0; i < labels.size(); i++ )
		delete labels[i];

	buttons.clear();
	labels.clear();
}

void UserInterface::draw( sf::RenderWindow* window )
{
	for ( Button* btn : buttons )
		btn->draw( window );
	for ( TextLabel* lbl : labels )
		lbl->draw( window );
}

void UserInterface::update( const sf::Vector2i* mouse_pos ) 
{
	last_event = UI_EVENT_NONE;
	for ( int b = 0; b < buttons.size(); b++ )
	{
		if ( buttons[b]->poll_is_clicked() )
			last_event = buttons[b]->get_event_code();

		buttons[b]->update( mouse_pos );
	}
}

bool UserInterface::on_mouse_up( int button, int x, int y )
{
	if ( button == sf::Mouse::Left )
	{
		// Tell each button to handle the click
		// If any button captures this event,
		// return true and exit this function
		for ( Button* btn : buttons )
			if ( btn->handle_click( x, y ) ) 
				return true;
	}

	return false;
}

TextLabel* UserInterface::create_label( int posx, int posy )
{
	TextLabel* lbl = new TextLabel(
		create_screen_coordinates( posx, posy )
	);
	labels.push_back( lbl );

	return lbl;
}

sf::Vector2f UserInterface::create_screen_coordinates( int posx, int posy )
{
	if ( posx < 0 ) posx = w_width + posx;
	if ( posy < 0 ) posy = w_height + posy;
	return sf::Vector2f( posx, posy );
}