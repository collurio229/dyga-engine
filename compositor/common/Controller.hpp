#ifndef CONTROLLER_DYGA_H
#define CONTROLLER_DYGA_H

#include <vector>

#include "SDL_events.h"

#include "Property.hpp"
#include "Visitor.hpp"

/*
 * The Controller class handles SDL events.
 */
typedef Visitor<SDL_Event*> EventListener;

class Controller
{
public:
	Controller() : events_()
	{
		for (int i = 0; i < SDL_LASTEVENT; i++)
		{
			SDL_Event event;
			events_.push_back(Property<SDL_Event*>(&event));
		}
	}

	~Controller() {}

	void bind(EventListener* visitor, SDL_EventType ev)
	{
		events_[ev].subscribe(visitor);
	}

	void read_events()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			events_[event.type].set(&event);
		}
	}

private:
	std::vector<Property<SDL_Event*>> events_;
};

#endif //DYGA_CONTROLLER_H
