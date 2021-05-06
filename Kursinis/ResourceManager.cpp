#include "ResourceManager.h"


ResourceManager::ResourceManager()
{

}

void ResourceManager::load_resources()
{
	load_texture( &textures[T_AND_GATE], "Assets/and-gate.png" );
	load_texture( &textures[T_OR_GATE], "Assets/or-gate.png" );
	load_texture( &textures[T_XOR_GATE], "Assets/xor-gate.png" );
	load_texture( &textures[T_NOT_GATE], "Assets/not-gate.png" );
	load_texture( &textures[T_ICON_AND], "Assets/and-icon.png" );
	load_texture( &textures[T_ICON_NOT], "Assets/not-icon.png" );
	load_texture( &textures[T_ICON_XOR], "Assets/xor-icon.png" );
	load_texture( &textures[T_ICON_OR], "Assets/or-icon.png" );
	load_texture( &textures[T_ICON_PLAY], "Assets/play-icon.png" );
	load_font( &fonts[F_MAIN_FONT], "Assets/Inconsolata.ttf" );
}	

void ResourceManager::load_texture( sf::Texture* texture, std::string path )
{
	if ( !texture->loadFromFile( path ) )
	{
		std::string message = "File not found: " + path;
		throw std::invalid_argument( message );
	}
	texture->setSmooth( true );
}

void ResourceManager::load_font( sf::Font* font, std::string path )
{
	if ( !font->loadFromFile( path ) )
	{
		std::string message = "File not found: " + path;
		throw std::invalid_argument( message );
	}
}

const sf::Texture* ResourceManager::get_texture( int texture_id ) const
{
	if ( texture_id == T_TOTAL ) return nullptr;

	return &textures[texture_id];
}

const sf::Font* ResourceManager::get_font( int font_id ) const
{
	if ( font_id == T_TOTAL ) return nullptr;

	return &fonts[font_id];
}