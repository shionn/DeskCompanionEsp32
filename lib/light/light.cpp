#include "light.h"

Light::Light(Display* display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
}

void Light::init() {
	this->iot->registerCaptor(201);
}

void Light::draw() {
	int y = 30;
	this->display->drawCenterText(160, y, "Lumière", RGB565_BLACK);

}


bool Light::update() {
	return false;
};

boolean Light::pressed(uint16_t touchX, uint16_t touchY) { return false; }
boolean Light::released(uint16_t touchX, uint16_t touchY) { return false; }
