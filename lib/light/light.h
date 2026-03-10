
#ifndef __LIGHT_h__
#define __LIGHT_h__

#include "display.h"
#include "homeiot.h"
#include "const.h"
#include "color-picker.h"

class Light {
private:
	Display* display;
	HomeIot* iot;
	int editColor = 0;
	ColorPicker* colorPicker;
public:
	Light(Display* display, HomeIot* iot);
	void init();
	bool update();

	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);

private:
	void drawColorRect(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);

};

#endif