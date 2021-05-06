#include "LevelLoader.h"


int LevelLoader::load_level_list()
{
	std::ifstream map;
	map.open( "Levels/levelmap.txt" );

	if ( !map.is_open() )
	{
		throw "Could not find level map (levelmap.txt)";
	}

	Level lvl;
	lvl.available_gates;
	reset_level_gates( lvl );
	int gates_loaded = 0;

	while ( !map.eof() )
	{
		std::string keyword;
		map >> keyword;

		if ( keyword == "LEVEL" )
		{
			std::string name;
			map.ignore( 100, '\n' );
			getline( map, name );

			lvl.name = trim_line( name );
			map >> lvl.inputs >> lvl.outputs;
		}
		else if ( keyword == "TESTS" )
		{
			std::string in, out;
			while ( true )
			{
				map >> in;
				if ( in == "END_TESTS" )
					break;

				map >> out;
				if ( out == "END_TESTS" )
					break;
				
				if ( in.size() != lvl.inputs )
					throw "Test input length mismatch.";
				if ( out.size() != lvl.outputs )
					throw "Test output length mismatch.";

				if ( !validate_test_case( in ) || !validate_test_case( out ) )
					throw "Unexpected symbol in test case";

				lvl.test_cases.push_back( { in, out } );
			}
		}
		else if ( keyword == "GATES" )
		{
			std::string gate;
			gates_loaded = 0;
			while ( gates_loaded < 10 )
			{
				map >> gate;
				if ( gate == "END_GATES" ) break;

				if ( gate == "AND" )
					lvl.available_gates[CircuitElementType::AND_GATE] = true;
				else if ( gate == "XOR" )
					lvl.available_gates[CircuitElementType::XOR_GATE] = true;
				else if ( gate == "OR" )
					lvl.available_gates[CircuitElementType::OR_GATE] = true;
				else if ( gate == "NOT" )
					lvl.available_gates[CircuitElementType::NOT_GATE] = true;
				else
					throw "Unknown gate";

				gates_loaded++;
			}
		}
		else if ( keyword == "END_LEVEL" )
		{
			// If no gates were specified in this level, just enable all of them
			if ( gates_loaded == 0 )
				reset_level_gates( lvl, true );

			levels.push_back( lvl );

			// Reset the placeholder level
			lvl.test_cases.clear();
			reset_level_gates( lvl );
			gates_loaded = 0;
		}

		if ( map.eof() )
			break;

		if ( map.fail() )
			throw "Error in parsing file. Make sure the syntax is correct";
	}

	return levels.size();
}


void LevelLoader::print_level_list()
{
	for ( int i = 0; i < levels.size(); i++ )
	{
		std::cout << i + 1 << ": " << levels[i].name << '\n';
	}
}

Level& LevelLoader::get_level( int ind )
{
	return levels[ind];
}

bool LevelLoader::validate_test_case( std::string& t )
{
	for ( char& c : t ) if ( c != '0' && c != '1' ) return false;
	return true;
}

void LevelLoader::reset_level_gates( Level& lvl, bool val )
{
	lvl.available_gates[CircuitElementType::AND_GATE] = val;
	lvl.available_gates[CircuitElementType::XOR_GATE] = val;
	lvl.available_gates[CircuitElementType::NOT_GATE] = val;
	lvl.available_gates[CircuitElementType::OR_GATE] = val;
}