#include <thread>

#include "Painter.h"

Painter::Painter()
: width(640, "width"), height(480, "height")
{
	width_.subscribe(this);
	height_.subscribe(this);
}

Painter::Painter(int height, int width)
: width_(width, "width"), height_(height, "height")
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

	running_.set(true);
	loop_ = new std::thread(run);
}

void Painter::call(Property<int>* prop)
{
	switch(prop->getId())
	{
	case "height":
	case "width":
		SDL_SetWindowSize(window_, width_, height_);
		break;
	}
}

void Painter::run()
{
	while(running_)
	{

	}
}

void Painter::stop()
{
	running_ = false;

	loop_->join();
	delete loop_;

	SDL_DestroyWindow(window_);
}
