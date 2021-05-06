#include "Circuit.h"

Circuit::Circuit()
{
	tmp_wire = new Wire;
}

Circuit::~Circuit()
{
	// Memory does not have to be freed manually, because
	// these objects should be managed by a different part 
	// of the application
	circuit_elements.clear();
	connection_points.clear();
}

void Circuit::register_circuit_element( CircuitElement* element )
{
	circuit_elements.push_back( element );
}

void Circuit::register_connection_point( ConnectionPoint* cp )
{
	connection_points.push_back( cp );
}

void Circuit::deregister_connection_point( ConnectionPoint* cp )
{
	// Erase all wires that are connected to this element
	for ( int w = 0; w < wires.size(); w++ )
	{
		if ( wires[w]->get_input_element() == cp ||
			wires[w]->get_output_element() == cp )
		{
			delete wires[w];
			wires.erase( wires.begin() + w );
			w--;
		}
	}

	// Now deregister this element
	for ( int i = 0; i < connection_points.size(); i++ )
	{
		if ( connection_points[i] == cp )
		{
			connection_points.erase( connection_points.begin() + i );
			return;
		}
	}
}

void Circuit::update( sf::Vector2f& mouse_pos )
{
	if ( !simulation_started )
	{
		for ( CircuitElement* cl : circuit_elements )
			cl->update( mouse_pos );
	}
	else 
	{
		for ( CircuitElement* cl : circuit_elements )
		{
			cl->update( mouse_pos );
			cl->execute();
		}
	}

	for ( Wire* wire : wires )
		wire->update( mouse_pos );

	if ( placing_wire )
		tmp_wire->set_end_pos( mouse_pos );
}

void Circuit::draw( sf::RenderWindow* window )
{
	render_lock.lock();

	for ( CircuitElement* cl : circuit_elements )
		cl->draw( window );

	for ( Wire* wire : wires )
		wire->draw( window );

	if ( placing_wire )
		tmp_wire->draw( window );

	render_lock.unlock();
}

bool Circuit::handle_mouse_click( sf::Vector2f& mouse_pos )
{
	for ( ConnectionPoint* cp : connection_points )
	{
		if ( cp->contains( mouse_pos ) )
		{
			// Clicked on one of the connection points
			if ( !placing_wire )
			{
				// Create a new wire from this point
				placing_wire = true;
				tmp_wire->set_start_pos( cp->get_position() );
				if ( cp->get_type() == ConnectionPointType::INPUT )
					tmp_wire->set_input_element( cp );
				else tmp_wire->set_output_element( cp );

				return true;
			}
			else
			{
				// Make sure we are connecting compatible points, i.e. input with output
				if ( cp->get_type() == ConnectionPointType::INPUT &&
					tmp_wire->get_input_element() == nullptr )
					tmp_wire->set_input_element( cp );
				else if ( cp->get_type() == ConnectionPointType::OUTPUT &&
					tmp_wire->get_output_element() == nullptr )
					tmp_wire->set_output_element( cp );
				else break;

				// Create a permanent wire between these two points
				tmp_wire->set_end_pos( cp->get_position() );
				
				render_lock.lock();
				wires.push_back( tmp_wire );
				tmp_wire = new Wire;
				render_lock.unlock();

				break;
			}
		}
	}

	if ( placing_wire )
	{
		placing_wire = false;
		// Reset temporary wire
		tmp_wire->set_input_element( nullptr );
		tmp_wire->set_output_element( nullptr );
		
		return true;
	}

	return false;
}

bool Circuit::handle_right_click( sf::Vector2f& mouse_pos )
{
	// Check if we have clicked on any of the wires
	for ( int i = 0; i < wires.size(); i++ )
	{
		if ( wires[i]->intersects( mouse_pos ) )
		{
			render_lock.lock();
			// Reset the output of the wire, if it exists
			if ( wires[i]->get_input_element() != nullptr )
				wires[i]->get_input_element()->set_state( ElementStates::DEFAULT );

			// Free memory to avoid memory leak
			delete wires[i];
			wires.erase( wires.begin() + i );
			render_lock.unlock();

			return true;
		}
	}

	for ( int i = 0; i < circuit_elements.size(); i++ )
	{
		if ( !circuit_elements[i]->intersects( mouse_pos ) ) continue;

		render_lock.lock();

		// Ask this circuit element to deregister it's connections
		circuit_elements[i]->deregister( this );

		// Delete it
		delete circuit_elements[i];
		circuit_elements.erase( circuit_elements.begin() + i );
		render_lock.unlock();
	}
}