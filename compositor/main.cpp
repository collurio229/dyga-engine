#include "Property.hpp"
#include "Visitor.hpp"
#include "Painter.h"
#include "QuitListener.hpp"

using namespace std;

int main(int argc, char** argv)
{
	Painter painter(360, 240, "foo");
	QuitListener quit(&painter);
	painter.start();
	while(painter.running_) {
		painter.controller.read_events();
	}
}
