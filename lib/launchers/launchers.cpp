#include "launchers.h"

Launchers::Launchers(Display* display) {
	this->display = display;
}

void Launchers::init() {
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
					// delay(1);
					// this->keyboard.print(this->toLocalFr(this->shortcuts[iy][ix].cmd));
					// delay(10);
					// this->keyboard.press(KEY_RETURN);
					// delay(1);
					// this->keyboard.releaseAll();
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
