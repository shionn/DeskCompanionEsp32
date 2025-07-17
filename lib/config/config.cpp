
#include "config.h"

Config::Config(Display* display) {
	this->display = display;
}

void Config::init() {
}

void Config::draw() {
	display->drawText(10, 25, String("Memory ") + String(esp_get_free_heap_size()), RGB565_BLACK);
	display->drawText(10, 45, String("Display FPS ") + (this->fps ? "true" : "false"), RGB565_BLACK);
}

bool Config::pressed(uint16_t touchX, uint16_t touchY) {
	return false;
}

bool Config::released(uint16_t touchX, uint16_t touchY) {
	if (touchY >= 45 && touchY <= 65) {
		this->fps = !this->fps;
		return true;
	}
	return false;
}

bool Config::isFpsEnable() {
	return this->fps;
}

