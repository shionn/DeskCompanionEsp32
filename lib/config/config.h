
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "display.h"

class Config {
private:
	Display* display;
public:
	Config(Display* display);

	void init();
	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);

};

#endif
