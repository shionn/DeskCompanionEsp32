#include "mode.h"

Mode::Mode(Display display) {
	this->display = display;
}

void Mode::draw() {
	if (this->value > 0) {
		this->display.fillCircle(14, 465, 12, RGB565_DARKGREY);
		this->display.fillTriangle(5, 465, 20, 460, 20, 470, RGB565_WHITE);
	}
	if (this->value < 1) {
		this->display.fillCircle(306, 465, 12, RGB565_DARKGREY);
		this->display.fillTriangle(315, 465, 300, 460, 300, 470, RGB565_WHITE);
	}
}

void Mode::touched(uint16_t touchX, uint16_t touchY) {
	if (touchX < 25 && touchY>455 && this->value > 0) {
		this->value--;
	}
	if (touchX > 295 && touchY > 455 && this->value < 1) {
		this->value++;
	}
}

int Mode::get() {
	return this->value;
}

