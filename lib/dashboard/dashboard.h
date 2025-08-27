
#ifndef __DASHBOARD_h__
#define __DASHBOARD_h__

#include "display.h"
#include "homeiot.h"
#include "const.h"

class Dashboard {
private:
	Display* display;
	HomeIot* iot;
	float_t cpu, gpuEdge, gpuJunc, nvme, office, bedroom, exterior;
	float_t elec_prod, elec_consso, pc_consso, hl_consso;
	long lastUpdated = 0;
public:
	Dashboard(Display* display, HomeIot* iot);
	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);
	bool update();

private:
	void drawTempBar(uint16_t y, String text, float_t value, uint16_t min, uint16_t max);
	void drawElecBar(uint16_t y, String text, float_t value, float_t min, float_t max);
	void drawWattBar(uint16_t y, String text, float_t value, float_t min, float_t max);
	void drawValueBar(uint16_t y, String text, float_t value, float_t min, float_t max, unsigned int decimal, String unit);
};


#endif