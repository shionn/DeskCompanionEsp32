#include "light.h"

Light::Light(Display* display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
	this->colorPicker = new ColorPicker(display);
}

void Light::init() {
	this->iot->registerCaptor(201);
}

void Light::drawColorRect(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
	this->display->fillRect(x * 50 + 10, 20 + y * 50, 50, 50, this->display->getGfx()->color565(r, g, b));
}

void Light::draw() {
	if (editColor) {
		colorPicker->draw();
	} else {
		if (this->iot->isOn(201)) {
			this->display->drawSprite(10, 30, toggle_on);
		} else {
			this->display->drawSprite(10, 30, toggle_off);
		}
		this->display->drawText(85, 35, "Lumiere test", RGB565_BLACK);
		this->display->drawSprite(246, 30, color_wheel);
	}
}

boolean Light::pressed(uint16_t touchX, uint16_t touchY) {
	boolean changed = false;
	if (editColor) {
		changed = colorPicker->pressed(touchX, touchY);
	}
	return changed;
};

boolean Light::released(uint16_t touchX, uint16_t touchY) {
	boolean changed = false;
	if (editColor) {
		if (colorPicker->released(touchX, touchY)) {
			editColor = 0;
			changed = true;
			iot->setCaptor(202, colorPicker->getColorHsvString());
		}
	} else if (display->isTouchOnSprite(10, 20, toggle_on)) {
		if (this->iot->isOn(201)) {
			this->iot->setOff(201);
		} else {
			this->iot->setOn(201);
		}
		changed = true;
	} else if (display->isTouchOnSprite(246, 30, color_wheel)) {
		String color = iot->getCaptor(202);
		uint16_t h = Color::stringToHue(color);
		uint16_t s = Color::stringToSat(color);
		uint16_t v = Color::stringToValue(color);
		colorPicker->open(h, s, v);
		editColor = 202;
		changed = true;
	}
	return changed;
};
