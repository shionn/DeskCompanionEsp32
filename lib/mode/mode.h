
#include "display.h"

#ifndef __MODE_H__
#define __MODE_H__


class Mode {
private:
	int value = 0;
	Display display;

public:
	Mode(Display display);

	void draw();
	void touched(uint16_t touchX, uint16_t touchY);
	int get();

};

#endif
