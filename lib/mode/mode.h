
#ifndef __MODE_H__
#define __MODE_H__

#include "display.h"
#include "dashboard.h"
#include "launchers.h"
#include "drawer.h"
#include "config.h"
#include "light.h"

#define MAX_MODE 4

class Mode {
private:
	int value = 1;
	Dashboard* dashboard;
	Light* light;
	Launchers* launchers;
	Drawer* drawers;
	Config* config;
	Display* display;

public:
	Mode(Dashboard* dashboard, Light* light, Launchers* launchers, Drawer* drawers, Display* display, Config* config);

	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);
	int get();

};

#endif
