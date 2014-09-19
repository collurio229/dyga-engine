#ifndef PAINTER_DYGA_H
#define PAINTER_DYGA_H

#include "SDL.h"
#include "SDL_video.h"
#include <iostream>

#include "Property.hpp"
#include "Visitor.hpp"

class Painter : Visitor<int> {
public:
	Painter();
	Painter(int width, int height);
	virtual ~Painter();

	/*
	 * Starts the SDL window and the Graphics loop thread.
	 */
	void start();

	/*
	 * Stops the SDL window and the Graphics loop thread.
	 */
	void stop();

	/*
	 * These are the public properties of the painter class, which
	 * control the SDL_window and other basic properties linked to
	 * all graphic concerns
	 */
	Property<int> width_;
	Property<int> height_;
	// Set this to false to stop the Graphics loop
	Property<bool> running_;

	/*
	 * This function is called if one of the int properties changes,
	 * and the SDL_window is changed accordingly
	 */
	void call(Property<int>* prop);

private:
	/*
	 * This function represents the graphics loop.
	 */
	void run();

	// the SDL_Window variable
	SDL_Window* window_;

	// variable for the Graphics loop execution thread
	std::thread loop_;
};

#endif // PAINTER_DYGA_H
