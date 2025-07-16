
#ifndef __MODE_H__
#define __MODE_H__

#include "display.h"
#include "dashboard.h"
#include "launchers.h"
#include "drawer.h"
#include "config.h"

#define MAX_MODE 3

class Mode {
private:
	int value = 0;
	Dashboard* dashboard;
	Launchers* launchers;
	Drawer* drawers;
	Config* config;
	Display* display;

public:
	Mode(Dashboard* dashboard, Launchers* launchers, Drawer* drawers, Display* display, Config* config);

	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);
	int get();

};

#endif
