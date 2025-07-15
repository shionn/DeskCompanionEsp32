
#ifndef __MODE_H__
#define __MODE_H__

#include "display.h"
#include "dashboard.h"
#include "launchers.h"
#include "drawer.h"

#define MAX_MODE 2

class Mode {
private:
	int value = 0;
	Dashboard* dashboard;
	Launchers* launchers;
	Drawer* drawers;
	Display* display;

public:
	Mode(Dashboard* dashboard, Launchers* launchers, Drawer* drawers, Display* display);

	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);
	int get();

};

#endif
