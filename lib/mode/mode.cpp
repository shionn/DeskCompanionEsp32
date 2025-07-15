#include "mode.h"

Mode::Mode(Dashboard* dashboard, Launchers* launchers, Drawer* drawers, Display* display) {
	this->dashboard = dashboard;
	this->launchers = launchers;
	this->drawers = drawers;
	this->display = display;
}

void Mode::draw() {
	if (this->value > 0) {
		this->display->fillCircle(14, 465, 12, RGB565_DARKGREY);
		this->display->fillTriangle(5, 465, 20, 460, 20, 470, RGB565_WHITE);
	}
	if (this->value < MAX_MODE) {
		this->display->fillCircle(306, 465, 12, RGB565_DARKGREY);
		this->display->fillTriangle(315, 465, 300, 460, 300, 470, RGB565_WHITE);
	}
}

bool Mode::pressed(uint16_t touchX, uint16_t touchY) {
	bool consummed = false;
	switch (value) {
	case 0:
		consummed = this->dashboard->pressed(touchX, touchY);
		break;
	case 1:
		consummed = this->launchers->pressed(touchX, touchY);
		break;
	case 2:
		consummed = this->drawers->pressed(touchX, touchY);
		break;
	}
	return consummed;
}

bool Mode::released(uint16_t touchX, uint16_t touchY) {
	bool consummed = false;
	switch (value) {
	case 0:
		consummed = this->dashboard->released(touchX, touchY);
		break;
	case 1:
		consummed = this->launchers->released(touchX, touchY);
		break;
	case 2:
		consummed = this->drawers->released(touchX, touchY);
		break;
	}
	if (!consummed) {
		if (touchX < 25 && touchY>455 && this->value > 0) {
			this->value--;
			consummed = true;
		}
		if (touchX > 295 && touchY > 455 && this->value < MAX_MODE) {
			this->value++;
			consummed = true;
		}
	}
	return consummed;
}

int Mode::get() {
	return this->value;
}

