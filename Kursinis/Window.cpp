#include "Window.h"


Window::Window( int width, int height )
	: width( width ), height( height )
{
	render_queue = new RenderQueue();

	window = new sf::RenderWindow(
		sf::VideoMode( width, height ),
		"Circuitz",
		sf::Style::Close | sf::Style::Titlebar
	);
}

Window::~Window()
{
	stop_render_thread();
	window->close();
	delete window;
}


void Window::start_render_thread()
{
	// Make sure current thread is not active
	if ( render_thread.joinable() ) return;

	// Deactivate window from this thread, so it can be moved to another one
	window->setActive( false );
	window_should_close = false;
	render_thread = std::thread( &Window::render, this );
}

void Window::stop_render_thread()
{
	// Make sure render thread is active
	if ( !render_thread.joinable() ) return;

	window_should_close = true;
	render_thread.join();
}

RenderQueue* Window::get_render_queue() { return render_queue; }

sf::RenderWindow* Window::get_window() { return window; }

void Window::render()
{
	while ( !window_should_close )
	{
		window->clear( sf::Color( 200, 200, 200 ) );

		render_queue->draw( window );

		window->display();
	}

	window->setActive( false );
}
