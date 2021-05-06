#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "Renderable.h"
#include "ConnectionPoint.h"
#include "Circuit.h"

// Dirty trick for cyclical dependencies
class Circuit;

#define CIRCUIT_ELEMENT_SIZE 256

class CircuitElement : public Renderable
{

public:
	~CircuitElement();
	void deregister( Circuit* circuit );

	virtual void draw( sf::RenderWindow* window );
	virtual void update( sf::Vector2f mouse_pos );
	// Reads and sets connections
	virtual void execute() {}

	bool intersects( sf::Vector2f pos );

protected:
	int posx, posy;

	sf::RectangleShape shape;

	std::vector<ConnectionPoint> connection_points;

	void register_connection_points( Circuit* circuit );
};

