#pragma once

#include "CircuitParams.h"
#include "Circuit.h"
#include "ConnectionPoint.h"

class SignalPoint : public CircuitElement
{
public:
	SignalPoint( int posx, int posy, Circuit* circuit );

	void set_state( bool val );

private:
};

