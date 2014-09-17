#include <thread>

#include "Painter.h"

Painter::Painter()
: width(640, "width"), height(480, "height")
{
	width.subscribe(this);
	height.subscribe(this);
}

Painter::Painter(int height, int width)
: width(width, "width"), height(height, "height")
{
	width.subscribe(this);
	height.subscribe(this);
}

Painter::~Painter()
{
}

void Painter::start()
{
	SDL_init(SDL_INIT_VIDEO);

	window_ = SDL_CreateWindow();

	if (window_ == NULL)
	{
	//TODO ERROR HANDLING
	}

	std::thread(run);
}

void Painter::call(Property<int>* prop)
{
	switch(prop->getId())
	{
	case "height":
	case "width":
		SDL_SetWindowSize(window_, width, height);
		break;
	}
}

void Painter::run()
{

}
