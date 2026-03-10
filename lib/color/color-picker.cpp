
#include "color-picker.h"

ColorPicker::ColorPicker(Display* display) {
	this->display = display;
};

void ColorPicker::open(uint16_t h,uint8_t s, uint8_t v) {
	this->h = h;
	this->s = s;
	this->v = v;
};

void ColorPicker::draw() {
	for (uint16_t i = 0; i < 300;i++) {
		uint16_t color = Color::hsvToRgb565(map(i, 0, 300, 0, 65535), s, v);
		display->drawVLine(10 + i, 32, 64, color);
	}

	for (uint16_t i = 0; i < 300;i++) {
		uint16_t color = Color::hsvToRgb565(h, map(i, 0, 300, 0, 255), v);
		display->drawVLine(10 + i, 128, 64, color);
	}

	for (uint16_t i = 0; i < 300;i++) {
		uint16_t color = Color::hsvToRgb565(h, s, map(i, 0, 300, 0, 255));
		display->drawVLine(10 + i, 224, 64, color);
	}

	display->fillRoundRect(10, 320, 300, 64, 16, Color::hsvToRgb565(h, s, v));
	display->drawRoundRect(10, 320, 300, 64, 16, RGB565_BLACK);
	display->drawCenterText(160, 344, "Valider",Color::hsvToRgb565(h+32768, s, v));
};

bool ColorPicker::pressed(uint16_t touchX, uint16_t touchY) {
	boolean changed = false;
	if (display->isTouchOnRect(10, 32, 300, 64)) {
		h = map(touchX, 10, 310, 0, 65535);
		changed = true;
	} else if (display->isTouchOnRect(10, 128, 300, 64)) {
		s = map(touchX, 10, 310, 0, 255);
		changed = true;
	} else if (display->isTouchOnRect(10, 224, 300, 64)) {
		v = map(touchX, 10, 310, 0, 255);
		changed = true;
	}
	return changed;
};

bool ColorPicker::released(uint16_t touchX, uint16_t touchY) {
	boolean changed = false;
	if (display->isTouchOnRect(10, 320, 300, 64)) {
		changed = true;
	}
	return changed;
};

String ColorPicker::getColorHsvString() {
	return Color::hsvToString(h, s, v);
};

