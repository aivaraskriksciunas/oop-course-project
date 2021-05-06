#pragma once

#include "SFML/Graphics.hpp"
#include "Renderable.h"
#include "MouseEventHandler.h"
#include "Button.h"
#include "EventManager.h"
#include "TextLabel.h"
#include "LevelLoader.h"
#include "CircuitParams.h"

#define BTN_SPACING 50;

enum UiEvents {
	UI_EVENT_NONE = -1,
	BTN_ADD_AND_GATE = 0,
	BTN_ADD_OR_GATE,
	BTN_ADD_XOR_GATE,
	BTN_ADD_NOT_GATE,
	BTN_START_SIMULATION,
};

class UserInterface : public Renderable, public MouseEventHandler
{
public:
	UserInterface( int w_widht, int w_height );
	~UserInterface();
	void create_buttons( Level& lvl );

	// From Renderable
	void draw( sf::RenderWindow* window );

	// From MouseEventHandler
	bool on_mouse_up( int button, int x, int y );

	void update( const sf::Vector2i* mouse_pos );

	int get_ui_event() { return last_event; }
	TextLabel* create_label( int posx, int posy );

private:
	std::vector<Button*> buttons;
	std::vector<TextLabel*> labels;

	int last_event;
	int w_width, w_height;

	sf::Vector2f create_screen_coordinates( int posx, int posy );
};

