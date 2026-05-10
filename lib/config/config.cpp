
#include "config.h"

Config::Config(Display* display, LastError* error) {
	this->display = display;
	this->error = error;
}

void Config::init() {
}

void Config::draw() {
	display->drawText(10, 25, String("Memory ") + String(esp_get_free_heap_size()), RGB565_BLACK);
	display->drawText(10, 45, String("Display FPS ") + (this->fps ? "true" : "false"), RGB565_BLACK);
	display->drawText(10, 65, String("IP ") + WiFi.localIP().toString(), RGB565_BLACK);
	display->drawText(10, 85, String("MAC ") + WiFi.macAddress(), RGB565_BLACK);
	display->drawText(10, 105, String("Error ") + error->getSource(), RGB565_BLACK);
	display->drawText(10, 125, error->getContent(), RGB565_BLACK);
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

