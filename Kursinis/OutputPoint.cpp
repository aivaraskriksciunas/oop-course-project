#include "OutputPoint.h"


OutputPoint::OutputPoint( int x, int y, Circuit* circuit )
{
	connection_points ={
		ConnectionPoint( x, y, ConnectionPointType::INPUT, 20 )
	};

	register_connection_points( circuit );
}

bool OutputPoint::get_state()
{
	return connection_points[0].get_state() == ElementStates::HIGH;
}
