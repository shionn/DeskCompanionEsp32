
#ifndef __DASHBOARD_h__
#define __DASHBOARD_h__

#include "display.h"
#include "homeiot.h"

class Dashboard {
private:
	Display display;
	HomeIot* iot;
	uint16_t cpu, gpu, nvme, office, bedroom;
	long lastUpdated = 0;
public:
	Dashboard(Display display, HomeIot* iot);
	void draw();
	void touched(uint16_t touchX, uint16_t touchY);
	void update();

private:
	void drawTemperatue(uint16_t y, String text, uint16_t value, uint16_t min, uint16_t max);
};


#endif