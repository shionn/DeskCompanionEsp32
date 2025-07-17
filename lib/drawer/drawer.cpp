
#include "drawer.h"

Drawer::Drawer(Display* display) {
	this->display = display;
}

void Drawer::draw() {
	// this->display->getGfx()->draw16bitRGBBitmap(0, 20, drawer_bitmap, 320, 430);
	for (uint8_t i = 0; i < 8; i++) {
		display->fillRect(40 + i * 30, 450, 30, 30, this->getColor(i));
	}
}

bool Drawer::pressed(uint16_t touchX, uint16_t touchY) {
	if (touchY > 20 && touchY < 450) {
		this->display->getGfx()->fillCircle(touchX, touchY, 2, getColor(this->color));
		// drawer_bitmap[(touchY - 20) * 320 + touchX] = getColor(this->color);
	}
	return false;
}

bool Drawer::released(uint16_t touchX, uint16_t touchY) {
	if (touchY >= 450) {
		if (touchX > 40 && touchX < 286) {
			int i = (touchX - 40) / 30;
			this->color = i;
			return true;
		}
	}
	return false;
}

uint16_t Drawer::getColor(uint8_t index) {
	uint16_t c = RGB565_BLACK;
	switch (index) {
	case 0:c = RGB565_WHITE;
		break;
	case 1:c = RGB565_RED;
		break;
	case 2:c = RGB565_GREEN;
		break;
	case 3:c = RGB565_BLUE;
		break;
	case 4:c = RGB565_YELLOW;
		break;
	case 5:c = RGB565_CYAN;
		break;
	case 6:c = RGB565_PINK;
		break;
	default:
	case 7:c = RGB565_BLACK;
		break;
	}
	return c;
}