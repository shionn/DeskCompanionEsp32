

#ifndef __TOP_BAR_H__
#define __TOP_BAR_H__

#include <Arduino.h>

#include "display.h"
#include "network.h"
#include "horloge.h"
#include "const.h"
#include "mode.h"
#include "config.h"

class TopBar {
private:
	Display* display;
	Horloge* horloge;
	Network* network;
	Mode* mode;
	Config* config;
public:
	TopBar(Display* display, Horloge* horloge, Network* network, Mode* mode, Config* config);

	void draw();
};

#endif