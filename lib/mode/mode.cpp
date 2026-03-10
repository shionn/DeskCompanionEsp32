#include "mode.h"

Mode::Mode(Dashboard* dashboard, Light* light, Launchers* launchers, Drawer* drawers, Display* display, Config* config) {
	this->dashboard = dashboard;
	this->light = light;
	this->launchers = launchers;
	this->drawers = drawers;
	this->display = display;
	this->config = config;
}

void Mode::draw() {
	switch (this->value) {
	default:
	case 0:
		this->dashboard->draw();
		break;
	case 1:
		this->light->draw();
		break;
	case 2:
		this->launchers->draw();
		break;
	case 3:
		this->drawers->draw();
		break;
	case 4:
		this->config->draw();
		break;
	}
	if (this->value > 0) {
		this->display->fillCircle(18, 462, 16, RGB565_BLACK);
		this->display->fillTriangle(5, 462, 25, 452, 25, 472, RGB565_LIGHTGREY);
	}
	if (this->value < MAX_MODE) {
		this->display->fillCircle(302, 462, 16, RGB565_BLACK);
		this->display->fillTriangle(315, 462, 295, 452, 295, 472, RGB565_LIGHTGREY);
	}
}

bool Mode::pressed(uint16_t touchX, uint16_t touchY) {
	// Serial.printf("pressed at %d %d\n", touchX, touchY);
	bool consummed = false;
	switch (value) {
	case 0:
		consummed = this->dashboard->pressed(touchX, touchY);
		break;
	case 1:
		consummed = this->light->pressed(touchX, touchY);
		break;
	case 2:
		consummed = this->launchers->pressed(touchX, touchY);
		break;
	case 3:
		consummed = this->drawers->pressed(touchX, touchY);
		break;
	case 4:
		consummed = this->config->pressed(touchX, touchY);
		break;
	}
	return consummed;
}

bool Mode::released(uint16_t touchX, uint16_t touchY) {
	Serial.printf("released at %d %d\n", touchX, touchY);
	bool consummed = false;
	switch (value) {
	case 0:
		consummed = this->dashboard->released(touchX, touchY);
		break;
	case 1:
		consummed = this->light->released(touchX, touchY);
		break;
	case 2:
		consummed = this->launchers->released(touchX, touchY);
		break;
	case 3:
		consummed = this->drawers->released(touchX, touchY);
		break;
	case 4:
		consummed = this->config->released(touchX, touchY);
		break;
	}
	if (!consummed) {
		if (touchX <= 34 && touchY >= 450 && this->value > 0) {
			this->value--;
			consummed = true;
		}
		if (touchX >= 286 && touchY >= 450 && this->value < MAX_MODE) {
			this->value++;
			consummed = true;
		}
	}
	return consummed;
}

int Mode::get() {
	return this->value;
}

