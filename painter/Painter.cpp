#include "Painter.h"

Painter::Painter()
: width_(640, "width"), height_(480, "height"), title_("dyga created", "Title"), controller()
{
	width_.subscribe(this);
	height_.subscribe(this);
	title_.subscribe(this);
}

Painter::Painter(int height, int width, std::string title)
: width_(width, "width"), height_(height, "height"), title_(title, "Title"), controller()
{
	width_.subscribe(this);
	height_.subscribe(this);
	title_.subscribe(this);
}

Painter::~Painter()
{
}

void Painter::start()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Unable to initialize SDL: " << std::endl << SDL_GetError();
		//TODO Create useful exceptions
		throw;
	}

	window_ = SDL_CreateWindow(title_.get().c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		height_,
		width_,
		SDL_WINDOW_OPENGL);

	if (window_ == NULL)
	{
	//TODO ERROR HANDLING
		std::cout << "Unable to create SDL window: " << std::endl << SDL_GetError();
		throw;
	}

	running_ = true;
	loop_ = std::thread(&Painter::run, this);
}

void Painter::call(Property<int>* prop)
{
	if (prop->getId() == "height" or prop->getId() == "width")
	{
		SDL_SetWindowSize(window_, width_, height_);
	}
}

void Painter::call(Property<std::string>* title)
{
	SDL_SetWindowTitle(window_, title->get().c_str());
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

	loop_.join();

	SDL_DestroyWindow(window_);

	SDL_Quit();
}
