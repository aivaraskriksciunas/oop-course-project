#include "Game.h"


Game::Game()
	: should_game_exit( false )
{}

Game::~Game()
{
	
}

bool Game::on_close()
{
	should_game_exit = true;
	return true;
}

void Game::start( Level& lvl, int window_width, int window_height )
{
	Window window( window_width, window_height );
	EventManager events;
	World gameWorld( window_width, window_height );
	LevelManager levelManager( lvl, &gameWorld );
	UserInterface ui( window_width, window_height );

	// Create world based on the level information
	gameWorld.setup_world( lvl );
	// Create additional ui elements, like labels, required
	// for the level manager
	levelManager.init_ui_elements( &ui );
	ui.create_buttons( lvl );

	// Setup event handling
	events.add_close_event_handler( this );
	events.add_mouse_event_handler( &ui );
	events.add_mouse_event_handler( &gameWorld );
	events.add_keyboard_event_handler( &levelManager );

	// Setup rendering
	window.get_render_queue()->add_to_queue( &gameWorld );
	window.get_render_queue()->add_to_queue( &ui );
	window.start_render_thread();

	should_game_exit = false;

	sf::Clock fpsTimer;

	const float time_per_frame = 1000. / 200.;
	while ( !should_game_exit )
	{
		fpsTimer.restart();

		// Get window events
		events.poll_window_events( window.get_window() );

		// Update game components
		gameWorld.update( events.get_mouse_position(), time_per_frame );
		ui.update( events.get_mouse_position() );
		levelManager.update();

		// Handle ui events and pass them over to 
		// specific components
		switch ( ui.get_ui_event() )
		{
		case BTN_ADD_AND_GATE:
			gameWorld.start_placing_circuit_element( CircuitElementType::AND_GATE );
			break;
		case BTN_ADD_OR_GATE:
			gameWorld.start_placing_circuit_element( CircuitElementType::OR_GATE );
			break;
		case BTN_ADD_XOR_GATE:
			gameWorld.start_placing_circuit_element( CircuitElementType::XOR_GATE );
			break;
		case BTN_ADD_NOT_GATE:
			gameWorld.start_placing_circuit_element( CircuitElementType::NOT_GATE );
			break;
		case BTN_START_SIMULATION:
			levelManager.start_validation();
			break;
		}

		gameWorld.set_input_disabled( levelManager.is_validation_running() );

		// Implement delay to limit framerate
		float delta_t = fpsTimer.getElapsedTime().asMilliseconds();
		float to_sleep = std::max( 0.f, time_per_frame - delta_t );
		sf::sleep( sf::milliseconds( to_sleep ) );
	}

	window.stop_render_thread();
}