#include "LevelManager.h"

LevelManager::LevelManager( Level lvl, World* world )
	: world( world ), level( lvl )
{
	passed_tests.resize( lvl.test_cases.size(), false );
}


bool LevelManager::on_key_up( sf::Event::KeyEvent ev )
{
	if ( validation_running ) return false;

	if ( ev.code == sf::Keyboard::Space || ev.code == sf::Keyboard::X )
	{
		current_test++;

		run_current_test();
		return true;
	}
	else if ( ev.code == sf::Keyboard::Z )
	{
		current_test--;

		run_current_test();
		return true;
	}

	return false;
}

void LevelManager::update()
{
	if ( current_test == -1 ) return;

	std::string output = world->get_data_from_circuit();
	if ( output == level.test_cases[current_test][1] )
	{
		statusText->set_color( sf::Color( 0, 180, 20 ) );
		passed_tests[current_test] = true;
	}
	else
	{
		statusText->set_color( sf::Color::Red );
		passed_tests[current_test] = false;
	}

	if ( validation_running && 
		delay_timer.getElapsedTime().asMilliseconds() > DELAY_BETWEEN_TESTS_MS )
	{
		current_test++;

		if ( current_test == level.test_cases.size() )
		{
			// We have done all the tests
			validation_running = false;

			all_tests_passed = true;
			int passed = 0;
			for ( bool i : passed_tests )
			{
				if ( !i ) all_tests_passed = false;
				else passed++;
			}

			if ( all_tests_passed )
			{
				successText->set_text( "Congratulations!" );
			}
			else
			{
				std::string txt;
				txt += "Passed ";
				txt += std::to_string( passed ) + "/";
				txt += std::to_string( level.test_cases.size() );
				txt += " tests";

				successText->set_text( txt );
			}

			// So it doesn't crash
			current_test -= 1;
		}
		else
		{
			run_current_test();
			delay_timer.restart();
		}
	}
}

void LevelManager::init_ui_elements( UserInterface* ui )
{
	statusText = ui->create_label( 10, 10 );
	successText = ui->create_label( 10, -40 );
}

void LevelManager::start_validation()
{
	if ( validation_running ) return;

	validation_running = true;
	delay_timer.restart();

	passed_tests.clear();
	passed_tests.resize( level.test_cases.size(), false );

	current_test = 0;
	run_current_test();

	successText->set_text( "Running tests..." );
}

bool LevelManager::is_validation_running()
{
	return validation_running;
}

bool LevelManager::have_all_tests_passed()
{
	return all_tests_passed;
}

void LevelManager::run_current_test()
{
	if ( current_test < 0 )
		current_test = level.test_cases.size() - 1;
	else if ( current_test >= level.test_cases.size() )
		current_test = 0;

	world->send_data_to_circuit( level.test_cases[current_test][0] );
	std::string text = "Test ";
	text += std::to_string( current_test + 1 );
	text += "/";
	text += std::to_string( level.test_cases.size() );

	statusText->set_text( text );
}