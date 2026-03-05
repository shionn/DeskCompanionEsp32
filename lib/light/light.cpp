#include "light.h"

Light::Light(Display* display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
}

void Light::draw() {


}


bool Light::update() {
	return false;
};

boolean Light::pressed(uint16_t touchX, uint16_t touchY) { return false; }
boolean Light::released(uint16_t touchX, uint16_t touchY) { return false; }
