#include "light.h"

Light::Light(Display* display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
}

void Light::init() {
	this->iot->registerCaptor(201);
}

void Light::draw() {
	if (this->iot->isOn(201)) {
		this->display->drawSprite(10, 30, toggle_on);
	} else {
		this->display->drawSprite(10, 30, toggle_off);
	}
	this->display->drawText(85, 35, "Lumiere test", RGB565_BLACK);

}


bool Light::update() {
	return true;
};

boolean Light::pressed(uint16_t touchX, uint16_t touchY) {
	return false;
}

boolean Light::released(uint16_t touchX, uint16_t touchY) {
	boolean changed = false;
	if (display->isTouchOnSprite(10, 20, toggle_on)) {
		if (this->iot->isOn(201)) {
			this->iot->setOff(201);
		} else {
			this->iot->setOn(201);
		}
		changed = true;
	}
	return changed;
}
