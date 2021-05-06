#pragma once

#include "CircuitParams.h"
#include "Circuit.h"
#include "ConnectionPoint.h"

class OutputPoint : public CircuitElement
{
public:
	OutputPoint( int posx, int posy, Circuit* circuit );

	bool get_state();

private:
};

