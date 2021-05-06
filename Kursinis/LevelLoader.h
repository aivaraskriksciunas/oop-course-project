#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include "Util.h"
#include "CircuitParams.h"

struct Level {
	std::string name;
	int inputs;
	int outputs;
	std::vector<std::array<std::string, 2>> test_cases;
	std::map<CircuitElementType, bool> available_gates;
};

class LevelLoader
{
public:
	int load_level_list();
	void print_level_list();
	Level& get_level( int ind );

private:
	std::vector<Level> levels;

	bool validate_test_case( std::string& t );
	void reset_level_gates( Level& lvl, bool val = false );
};

