
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <WiFi.h>
#include "display.h"
#include "error.h"


class Config {
private:
	Display* display;
	LastError* error;
	bool fps = false;
public:
	Config(Display* display, LastError* error);

	void init();
	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);

	bool isFpsEnable();

};

#endif
