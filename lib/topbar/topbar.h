
#include <Arduino.h>

#include "display.h"
#include "network.h"
#include "horloge.h"
#include "const.h"

#ifndef __TOP_BAR_H__
#define __TOP_BAR_H__

class TopBar {
private:
	Display display;
	Horloge horloge;
	Network network;
public:
	TopBar(Display display, Horloge horloge, Network network);

	void draw();
};

#endif