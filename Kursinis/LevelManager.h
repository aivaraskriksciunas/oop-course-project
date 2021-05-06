#pragma once

#include <string>
#include "KeyboardEventHandler.h"
#include "World.h"
#include "UserInterface.h"
#include "TextLabel.h"

#define DELAY_BETWEEN_TESTS_MS 200

class LevelManager : public KeyboardEventHandler
{
public:
	LevelManager( Level lvl, World* world );

	bool on_key_up( sf::Event::KeyEvent ev );

	void init_ui_elements( UserInterface* ui );
	void update();
	void start_validation();
	bool is_validation_running();
	bool have_all_tests_passed();

private:
	World* world;
	Level level;

	int current_test = -1;

	// Validation of the circuit
	bool validation_running = false;
	sf::Clock delay_timer;
	std::vector<bool> passed_tests;
	bool all_tests_passed = false;

	TextLabel* statusText = nullptr;
	TextLabel* successText = nullptr;

	void run_current_test();
};

