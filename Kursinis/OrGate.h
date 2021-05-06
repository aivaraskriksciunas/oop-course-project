#pragma once

#include "SFML/Graphics.hpp"
#include "CircuitElement.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "ConnectionPoint.h"
#include "Circuit.h"

class OrGate : public CircuitElement
{
public:
	OrGate( int posx, int posy, Circuit* circuit );

	void execute();

private:

};

