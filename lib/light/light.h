
#ifndef __LIGHT_h__
#define __LIGHT_h__

#include "display.h"
#include "homeiot.h"
#include "const.h"

class Light {
private:
	Display* display;
	HomeIot* iot;
public:
	Light(Display* display, HomeIot* iot);
	void init();
	bool update();
	
	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);

}


#endif