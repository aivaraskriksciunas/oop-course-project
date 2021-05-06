#include "World.h"

World::World( int w_width, int w_height ) : 
	placing_element( CircuitElementType::NONE ),
	w_width( w_width ), w_height( w_height ),
	ratio( w_width / (double) w_height )
{
	to_place.setFillColor( sf::Color( 12, 242, 91 ) );
	to_place.setSize( sf::Vector2f( CIRCUIT_ELEMENT_SIZE, CIRCUIT_ELEMENT_SIZE ) );

	view.setCenter( w_width / 2, w_height / 2 );
	view.setSize( w_width, w_height );
}

World::~World()
{
	for ( int i = 0; i < input_points.size(); i++ )
		delete input_points[i];

	input_points.clear();
}

void World::setup_world( Level& lvl )
{
	for ( int p = 0; p < lvl.inputs; p++ )
		input_points.push_back( new SignalPoint( 10, 10 + p * INPUT_POINT_SPACING, &circuit ) );

	for ( int p = 0; p < lvl.outputs; p++ )
		output_points.push_back( new OutputPoint( 1600, 10 + p * OUTPUT_POINT_SPACING, &circuit ) );


	for ( SignalPoint* sp : input_points )
		circuit.register_circuit_element( sp );

	for ( OutputPoint* op : output_points )
		circuit.register_circuit_element( op );
}

void World::draw( sf::RenderWindow* window )
{
	// Start drawing on our special view
	window->setView( view );

	std::lock_guard<std::mutex> lock( thread_lock );

	circuit.draw( window );

	if ( placing_element != CircuitElementType::NONE )
	{
		window->draw( to_place );
	}

	// Reset the view to default to not affect how 
	// other elements are drawn
	window->setView( window->getDefaultView() );
}

void World::update( const sf::Vector2i* mouse_pos, double delta_t )
{
	sf::Vector2f world_pos = screen_to_world_pos(
		sf::Vector2f( mouse_pos->x, mouse_pos->y )
	);

	if ( placing_element != CircuitElementType::NONE )
	{
		to_place.setPosition( world_pos );
	}
	else
	{
		circuit.update( world_pos );
	}

	// Move viewpoint
	sf::Vector2f view_offset( 0, 0 );
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
	{
		view_offset.y = -view_move_speed * delta_t;
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
	{
		view_offset.y = view_move_speed * delta_t;
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
	{
		view_offset.x = -view_move_speed * delta_t;
	}
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
	{
		view_offset.x = view_move_speed * delta_t;
	}

	view.setCenter( view.getCenter() + view_offset );
}

void World::start_placing_circuit_element( CircuitElementType type )
{
	placing_element = type;
}

void World::place_circuit_element()
{
	// Before placing this element, lock this thread
	std::lock_guard<std::mutex> lock( thread_lock );

	// Get placeholder position
	sf::Vector2f pos = to_place.getPosition();

	// Create a new element instance in specified world position
	CircuitElement* element;
	switch ( placing_element )
	{
	case CircuitElementType::AND_GATE:
		element = new AndGate( pos.x, pos.y, &circuit );
		break;
	case CircuitElementType::OR_GATE:
		element = new OrGate( pos.x, pos.y, &circuit );
		break;
	case CircuitElementType::XOR_GATE:
		element = new XorGate( pos.x, pos.y, &circuit );
		break;
	case CircuitElementType::NOT_GATE:
		element = new NotGate( pos.x, pos.y, &circuit );
		break;
	default:
		throw "Unknown circuit element";
	}

	circuit.register_circuit_element( element );

	// Stop placing element
	placing_element = CircuitElementType::NONE;
}

bool World::on_mouse_up( int button, int x, int y )
{
	if ( input_disabled ) return false;

	if ( button == sf::Mouse::Left && 
		placing_element != CircuitElementType::NONE )
	{
		place_circuit_element();
	}

	sf::Vector2f world_pos = screen_to_world_pos( sf::Vector2f( x, y ) );
	if ( button == sf::Mouse::Left )
	{
		circuit.handle_mouse_click( world_pos );
	}
	else if ( button == sf::Mouse::Right )
	{
		circuit.handle_right_click( world_pos );
	}

	// TODO: change return type based on whether event was used
	return true;
}

bool World::on_mouse_scroll( float delta, int x, int y )
{
	sf::Vector2f resized = view.getSize();
	resized.x += ( scroll_speed * -delta ) * ratio;
	resized.y += ( scroll_speed * -delta );

	view.setSize( resized );
	return true;
}

sf::Vector2f World::screen_to_world_pos( sf::Vector2f pos )
{
	sf::Vector2f relative_pos(
		pos.x / (float)w_width - 0.5f,
		pos.y / (float)w_height - 0.5f );

	sf::Vector2f wp = view.getCenter() + (view.getSize() * relative_pos);
	return wp;
}

void World::send_data_to_circuit( std::string data )
{
	circuit.set_simulation_started( true );

	// Set all inputs in order
	for ( int i = 0; i < input_points.size() && i < data.size(); i++ )
	{
		input_points[i]->set_state( data[i] == '1' );
	}
}


std::string World::get_data_from_circuit()
{
	std::string res = "";

	// Retrieve output voltage
	for ( OutputPoint* op : output_points )
		res += op->get_state() ? "1" : "0";

	return res;
}

void World::set_input_disabled( bool disable )
{
	input_disabled = disable;
}