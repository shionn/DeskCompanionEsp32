
#include "topbar.h"

TopBar::TopBar(Display* display, Horloge* horloge, Network* network, Mode* mode) {
	this->display = display;
	this->horloge = horloge;
	this->network = network;
	this->mode = mode;
};

// TODO calcul de fps
void TopBar::draw() {
	display->fillRect(0, 0, 320, 18, RGB565_BLACK);
	String date = horloge->getHour() < 10 ? "0" + String(horloge->getHour()) : String(horloge->getHour());
	date += (horloge->getSecond()) % 2 ? ":" : " ";
	date += horloge->getMinute() < 10 ? "0" + String(horloge->getMinute()) : String(horloge->getMinute());
	display->drawCenterText(160, 2, date, RGB565_WHITE);
	if (network->connected()) {
		display->drawSprite(306, 3, (uint16_t*)wifi);
	}
	for (int i = 0; i <= MAX_MODE; i++) {
		if (i == mode->get()) {
			display->fillCircle(5 + i * 9, 9, 3, RGB565_WHITE);
		} else {
			display->drawCircle(5 + i * 9, 9, 3, RGB565_WHITE);
		}
	}
};



