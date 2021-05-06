#include "SignalPoint.h"


SignalPoint::SignalPoint( int x, int y, Circuit* circuit )
{
	connection_points = {
		ConnectionPoint( x, y, ConnectionPointType::OUTPUT, 15 )
	};
	
	register_connection_points( circuit );
}

void SignalPoint::set_state( bool state )
{
	connection_points[0].set_state( state ? ElementStates::HIGH : ElementStates::LOW );
}

