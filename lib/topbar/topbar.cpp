
#include "topbar.h"

TopBar::TopBar(Display* display, Horloge* horloge, Network* network, Mode* mode, Config* config) {
	this->display = display;
	this->horloge = horloge;
	this->network = network;
	this->mode = mode;
	this->config = config;
};

u_int32_t last = millis();

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
	if (this->config->isFpsEnable()) {
		uint32_t current = millis();
		this->display->drawCenterText(240, 2, String(1000 / (current - last)), RGB565_WHITE);
		last = current;
	}
};



