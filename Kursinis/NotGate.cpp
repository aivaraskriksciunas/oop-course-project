#include "NotGate.h"


NotGate::NotGate( int posx, int posy, Circuit* circuit )
{
	const ResourceManager* rmanager = ServiceLocator::get_resource_manager();

	shape.setTexture( rmanager->get_texture( T_NOT_GATE ) );
	shape.setPosition( sf::Vector2f( posx, posy ) );
	shape.setSize( sf::Vector2f( CIRCUIT_ELEMENT_SIZE, CIRCUIT_ELEMENT_SIZE ) );

	connection_points ={
		ConnectionPoint( 0, 128, posx, posy, ConnectionPointType::INPUT ),
		ConnectionPoint( 256, 128, posx, posy, ConnectionPointType::OUTPUT )
	};

	register_connection_points( circuit );

}

void NotGate::execute()
{
	if ( connection_points[0].get_state() == ElementStates::HIGH )
	{
		connection_points[1].set_state( ElementStates::LOW );
	}
	else if( connection_points[0].get_state() == ElementStates::LOW )
	{
		connection_points[1].set_state( ElementStates::HIGH );
	}
	else connection_points[1].set_state( ElementStates::LOW );
}


