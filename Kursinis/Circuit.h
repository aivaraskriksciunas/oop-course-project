#pragma once

#include "SFML/Graphics.hpp"
#include "CircuitElement.h"
#include "ConnectionPoint.h"
#include "CircuitParams.h"
#include "Wire.h"
#include <mutex>

class CircuitElement;

class Circuit
{
public:
	Circuit();
	~Circuit();

	void register_circuit_element( CircuitElement* element );
	void register_connection_point( ConnectionPoint* cp );
	void deregister_connection_point( ConnectionPoint* cp );

	void update( sf::Vector2f& mouse_pos );
	void draw( sf::RenderWindow* window );

	bool handle_mouse_click( sf::Vector2f& mouse_pos );
	bool handle_right_click( sf::Vector2f& mouse_pos );

	void set_simulation_started( bool state ) { simulation_started = state; }

private:
	std::mutex render_lock;

	std::vector<CircuitElement*> circuit_elements;
	std::vector<ConnectionPoint*> connection_points;
	std::vector<Wire*> wires;

	// Temporary wire
	bool placing_wire = false;
	Wire* tmp_wire;

	bool simulation_started = false;
};

