#include "launchers.h"

Launchers::Launchers(Display* display, Storage* storage) {
	this->display = display;
	this->storage = storage;
}

void Launchers::init() {
#ifndef __SPRITE_FROM_FLASH__
	for (int iy = 0; iy < 5; iy++) {
		for (int ix = 0; ix < 4; ix++) {
			String file = String("/launcher/") + String(iy * 4 + ix + 1) + String(".bmp");
			const uint16_t* buffer = this->storage->readSprite(file.c_str());
			if (buffer) {
				this->shortcuts[iy][ix].icon = buffer;
			}
		}
	}
#endif
	// this->keyboard.begin();
}

void Launchers::draw() {
	for (int ix = 0; ix < 4; ix++) {
		for (int iy = 0; iy < 5; iy++) {
			if (this->shortcuts[iy][ix].icon) {
				this->drawicon(ix, iy, this->shortcuts[iy][ix].icon);
			}
		}
	}
}

void Launchers::drawicon(uint16_t ix, uint16_t iy, const uint16_t* icon) {
	int x = ix * 64 + 8 + 16 * ix;
	int y = iy * 64 + 26 + 16 * iy;
	this->display->drawSprite(x, y, icon);
	// this->display.getGfx()->drawRoundRect(x, y, 64, 64, 8, RGB565_BLACK);
}

bool Launchers::pressed(uint16_t touchX, uint16_t touchY) {
	return false;
}

bool Launchers::released(uint16_t touchX, uint16_t touchY) {
	if (!this->initialized) {
		USB.begin();
		keyboard.begin();
		this->initialized = true;
	}
	for (int ix = 0; ix < 4; ix++) {
		for (int iy = 0; iy < 5; iy++) {
			int x = ix * 64 + 8 + 16 * ix;
			int y = iy * 64 + 26 + 16 * iy;
			if (touchX >= x && touchX < x + 64 && touchY >= y && touchY < y + 64) {
				if (this->shortcuts[iy][ix].icon) {
					this->keyboard.press(KEY_LEFT_CTRL);
					this->keyboard.press(this->shortcuts[iy][ix].key);
					this->keyboard.releaseAll();
					return true;
				}
			}
		}
	}
	return false;
}

String Launchers::toLocalFr(String cmd) {
	cmd.replace('a', 'q');
	cmd.replace('m', ';');
	cmd.replace('/', '>');
	cmd.replace('-', '6');
	cmd.replace(':', '.');
	return cmd;
}
