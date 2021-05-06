#pragma once

#include "SFML/Graphics.hpp"
#include <string>

enum Textures {
	T_AND_GATE = 0,
	T_OR_GATE,
	T_XOR_GATE,
	T_NOT_GATE,
	T_ICON_AND,
	T_ICON_OR,
	T_ICON_XOR,
	T_ICON_NOT,
	T_ICON_PLAY,
	T_TOTAL
};

enum Fonts {
	F_MAIN_FONT,
	F_TOTAL
};

class ResourceManager
{
public:
	ResourceManager();

	void load_resources();
	const sf::Texture* get_texture( int texture_id ) const;
	const sf::Font* get_font( int font_id ) const;

private:
	sf::Texture textures[T_TOTAL];
	sf::Font fonts[F_TOTAL];

	void load_texture( sf::Texture* texture, std::string path );
	void load_font( sf::Font* font, std::string path );
};

