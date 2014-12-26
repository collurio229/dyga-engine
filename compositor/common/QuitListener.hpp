#ifndef QUITLISTENER_DYGA_H
#define QUITLISTENER_DYGA_H

#include "Controller.hpp"

class QuitListener : EventListener
{
public:

	QuitListener(Painter* painter)
	: to_be_closed_(painter)
	{
		to_be_closed_->controller.bind(this, SDL_QUIT);
	}

	~QuitListener() {}

	void call(Property<SDL_Event*>* prop)
	{
		to_be_closed_->stop();
	}

private:
	Painter* to_be_closed_;
};

#endif
