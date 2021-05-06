#pragma once

#include "SFML/Graphics.hpp"

enum class CircuitElementType {
	AND_GATE,
	OR_GATE,
	NOT_GATE,
	XOR_GATE,
	NONE,
};

enum class ElementStates {
	DEFAULT,
	LOW,
	HIGH,
};

enum class ConnectionPointType {
	INPUT,
	OUTPUT,
};

const sf::Color RED ( 200, 0,   0 );
const sf::Color BLUE( 0,   0, 100 );