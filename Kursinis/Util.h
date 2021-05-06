#pragma once

#include "SFML/Graphics.hpp"
#include <string>

template<class T, class F>
sf::Vector2<T> operator+( sf::Vector2<T> vec, F arg )
{
	return sf::Vector2<T>(
		vec.x + arg,
		vec.y + arg
	);
}

template<class T>
sf::Vector2<T> operator*( sf::Vector2<T> a1, sf::Vector2<T> a2 )
{
	return sf::Vector2<T>( a1.x * a2.x, a1.y * a2.y );
}

// Remove spaces from start and end of the string
std::string trim_line( std::string line );