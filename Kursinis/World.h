#pragma once

#include <mutex>
#include <string>
#include "SFML/Graphics.hpp"
#include "Renderable.h"
#include "MouseEventHandler.h"
#include "ResourceManager.h"
#include "Util.h"
#include "CircuitParams.h"
#include "Circuit.h"
#include "AndGate.h"
#include "OrGate.h"
#include "XorGate.h"
#include "NotGate.h"
#include "SignalPoint.h"
#include "OutputPoint.h"
#include "LevelLoader.h"

#define INPUT_POINT_SPACING 80
#define OUTPUT_POINT_SPACING 100

class World : 
	public Renderable, 
	public MouseEventHandler
{

public:
	World( int w_width, int w_height );
	~World();

	// Initializes the world by placing level specific circuit elements
	void setup_world( Level& lvl );

	// From Renderable
	void draw( sf::RenderWindow* window );
	// From MouseEventHandler
	bool on_mouse_up( int button, int posx, int posy );
	bool on_mouse_scroll( float delta, int x, int y );

	void update( const sf::Vector2i* mouse_pos, double delta_t );

	void start_placing_circuit_element( CircuitElementType type );
	void place_circuit_element();

	// Interfacing with the circuit
	void send_data_to_circuit( std::string data );
	std::string get_data_from_circuit();

	sf::Vector2f screen_to_world_pos( sf::Vector2f pos );
	void set_input_disabled( bool disable );

private:

	std::mutex thread_lock;
	Circuit circuit;

	// View that will allow us to move around the world
	sf::View view;

	// A placeholder element to show when a circuit element 
	// is being dragged by the user
	CircuitElementType placing_element;
	sf::RectangleShape to_place;

	std::vector<SignalPoint*> input_points;
	std::vector<OutputPoint*> output_points;

	const int scroll_speed = 200;
	const int w_width, w_height;
	const float ratio;
	const double view_move_speed = 1.;
	bool input_disabled = false;
};

