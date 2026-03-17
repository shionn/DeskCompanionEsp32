#include "light.h"

Light::Light(Display* display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
	this->colorPicker = new ColorPicker(display);
}

void Light::init() {
	this->iot->registerCaptor(DESK_ROOF_LIGHT_STATE);
	this->iot->registerCaptor(DESK_ROOF_LIGHT_HSV);
	this->iot->registerCaptor(DESK_ROOF_LIGHT_HSV_2);
	this->iot->registerCaptor(DESK_ROOF_LIGHT_MODE);
	this->iot->registerCaptor(DESK_SHELF_LIGHT_STATE);
	this->iot->registerCaptor(DESK_SHELF_LIGHT_HSV);
	this->iot->registerCaptor(DESK_SHELF_LIGHT_HSV_2);
	this->iot->registerCaptor(DESK_SHELF_LIGHT_MODE);
}

void Light::drawColorRect(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
	this->display->fillRect(x * 50 + 10, 20 + y * 50, 50, 50, this->display->getGfx()->color565(r, g, b));
}

void Light::draw() {
	if (editColor) {
		colorPicker->draw();
	} else {
		this->drawLightLine(DESK_ROOF_LIGHT_STATE, 0, F("Plafon"), DESK_ROOF_LIGHT_MODE);
		this->drawLightLine(DESK_SHELF_LIGHT_STATE, 1, F("Etagere"), DESK_SHELF_LIGHT_MODE);
	}
}

void Light::drawLightLine(uint8_t captor, uint16_t y, String name, uint8_t captorMode) {
	uint16_t lineY = 32 + y * color_wheel[1] + 16 * y;
	uint16_t lineX = 8;
	this->display->drawSprite(lineX, lineY, color_wheel);
	lineX += color_wheel[0] + 8;
	this->display->drawSprite(lineX, lineY, color_wheel);
	lineX += color_wheel[0] + 8;
	if (this->iot->isOn(captor)) {
		this->display->drawSprite(lineX, lineY, toggle_v_on);
	} else {
		this->display->drawSprite(lineX, lineY, toggle_v_off);
	}
	lineX += toggle_v_on[0] + 8;
	this->display->drawText(lineX, lineY + 16, name, RGB565_BLACK);
	String mode = iot->getCaptor(captorMode);
	this->display->drawText(lineX, lineY + 16 + 24, mode, RGB565_BLACK);
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
			changed = true;
			iot->setCaptor(editColor, colorPicker->getColorHsvString());
			editColor = 0;
		}
	} else {
		changed = testColorPick(DESK_ROOF_LIGHT_HSV, 0, 0);
		changed = changed || testColorPick(DESK_ROOF_LIGHT_HSV_2, 1, 0);
		changed = changed || testTogglePick(DESK_ROOF_LIGHT_STATE, 0);
		changed = changed || testModePick(DESK_ROOF_LIGHT_MODE, 0);
		changed = changed || testColorPick(DESK_SHELF_LIGHT_HSV, 0, 1);
		changed = changed || testColorPick(DESK_SHELF_LIGHT_HSV_2, 1, 1);
		changed = changed || testTogglePick(DESK_SHELF_LIGHT_STATE, 1);
		changed = changed || testModePick(DESK_SHELF_LIGHT_MODE, 1);
	}
	return changed;
};

boolean Light::testColorPick(uint8_t captor, uint16_t x, uint16_t y) {
	uint16_t lineX = 8 + x * color_wheel[0] + 8 * x;
	uint16_t lineY = 32 + y * color_wheel[1] + 16 * y;
	if (display->isTouchOnSprite(lineX, lineY, color_wheel)) {
		String color = iot->getCaptor(captor);
		uint16_t h = Color::stringToHue(color);
		uint16_t s = Color::stringToSat(color);
		uint16_t v = Color::stringToValue(color);
		colorPicker->open(h, s, v);
		editColor = captor;
		return true;
	}
	return false;
}

boolean Light::testTogglePick(uint8_t captor, uint16_t y) {
	uint16_t lineX = 8 + color_wheel[0] + 8 + color_wheel[0] + 8;
	uint16_t lineY = 32 + y * color_wheel[1] + 16 * y;
	if (display->isTouchOnRect(lineX, lineY, 32, 64)) {
		if (this->iot->isOn(captor)) {
			this->iot->setOff(captor);
		} else {
			this->iot->setOn(captor);
		}
		return true;
	}
	return false;
};

boolean Light::testModePick(uint8_t captor, uint16_t y) {
	uint16_t lineX = 8 + color_wheel[0] + 8 + color_wheel[0] + 8 + 32 + 8;
	uint16_t lineY = 32 + y * color_wheel[1] + 16 * y;
	if (display->isTouchOnRect(lineX, lineY, 100, 64)) {
		String mode = iot->getCaptor(captor);
		if (mode.equalsIgnoreCase(F("static"))) {
			iot->setCaptor(captor, F("rainbow"));
		} else if (mode.equalsIgnoreCase(F("rainbow"))) {
			iot->setCaptor(captor, F("theatre"));
		} else if (mode.equalsIgnoreCase(F("theatre"))) {
			iot->setCaptor(captor, F("breath"));
		} else if (mode.equalsIgnoreCase(F("breath"))) {
			iot->setCaptor(captor, F("crawl"));
		} else {
			iot->setCaptor(captor, F("static"));
		}
		return true;
	}
	return false;
};

