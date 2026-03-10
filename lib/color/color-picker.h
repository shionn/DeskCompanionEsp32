#ifndef __COLOR_PICKER_H__
#define __COLOR_PICKER_H__

#include <Arduino.h>
#include "display.h"
#include "color.h"

class ColorPicker {

private:
	uint16_t h = 0; uint8_t s = 255, v=255;
	Display* display;

public:
	ColorPicker(Display* display);
	void open(uint16_t h, uint8_t s, uint8_t v);
	void draw();

	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);
	String getColorHsvString();
};
#endif
