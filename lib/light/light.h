
#ifndef __LIGHT_h__
#define __LIGHT_h__

#include "display.h"
#include "homeiot.h"
#include "const.h"
#include "color-picker.h"

#define DESK_ROOF_LIGHT_STATE 130
#define DESK_ROOF_LIGHT_HSV 131
#define DESK_ROOF_LIGHT_HSV_2 132
#define DESK_ROOF_LIGHT_MODE 133

#define DESK_SHELF_LIGHT_STATE 135
#define DESK_SHELF_LIGHT_HSV 136
#define DESK_SHELF_LIGHT_HSV_2 137
#define DESK_SHELF_LIGHT_MODE 138

class Light {
private:
	Display* display;
	HomeIot* iot;
	int editColor = 0;
	ColorPicker* colorPicker;
public:
	Light(Display* display, HomeIot* iot);
	void init();
	boolean update();

	void draw();
	boolean pressed(uint16_t touchX, uint16_t touchY);
	boolean released(uint16_t touchX, uint16_t touchY);

private:
	void drawColorRect(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
	void drawLightLine(uint8_t captor, uint16_t y, String name, uint8_t captorMode);
	boolean testColorPick(uint8_t captor, uint16_t x, uint16_t y);
	boolean testTogglePick(uint8_t captor, uint16_t y);
	boolean testModePick(uint8_t captor, uint16_t y);
};

#endif