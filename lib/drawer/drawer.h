#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <Arduino.h>

#include "display.h"

class Drawer {
private:
	Display* display;
	uint8_t color = 0;
public:
	Drawer(Display* display);
	void draw();
	void touched(uint16_t touchX, uint16_t touchY);
	uint16_t getColor(uint8_t index);
};


#endif