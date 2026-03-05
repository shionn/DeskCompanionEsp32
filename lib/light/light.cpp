#include "light.h"

Light::Light(Display* display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
}

void Light::init() {
	this->iot->registerCaptor(201);
}

void Light::draw() {
	if (this->iot->getCaptor(201).equalsIgnoreCase("on")) {
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
	if (touchX >= 10 && touchX < 10 + 64 && touchY >= 30 && touchY < 30 + 25) {
		if (this->iot->getCaptor(201).equalsIgnoreCase("on")) {
			this->iot->setCaptor(201, "off");
		} else {
			this->iot->setCaptor(201, "on");
		}
		changed = true;
	}

	return changed;
}
