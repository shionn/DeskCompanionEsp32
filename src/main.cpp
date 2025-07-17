
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <WiFi.h>
#include <SD_MMC.h>

#include "dashboard.h"
#include "display.h"
#include "drawer.h"
#include "horloge.h"
#include "homeiot.h"
#include "launchers.h"
#include "topbar.h"
#include "mode.h"
#include "network.h"
#include "storage.h"
#include "config.h"

Network network;
HomeIot homeiot;
Horloge horloge;
Display display;
Storage storage;

Config config(&display);
Dashboard dashboard(&display, &homeiot);
Launchers launchers(&display, &storage);
Drawer drawer(&display);
Mode mode(&dashboard, &launchers, &drawer, &display, &config);
TopBar topbar(&display, &horloge, &network, &mode, &config);

// uint16_t* buffer[20];

void setup() {
	Serial.begin(115200);

	display.init();
	display.fillScreen(RGB565_WHITE);
	display.drawCenterText(160, 240, F("Starting..."), RGB565_BLACK);
	display.flush();

	network.init();
#ifndef __SPRITE_FROM_FLASH__
	storage.init();
#endif
	launchers.init();
	horloge.init();

}

bool touch = false;

void loop() {
	bool changed = dashboard.update();
	if (display.isTouched()) {
		touch = true;
		changed |= mode.pressed(display.touchX, display.touchY);
	} else if (touch) {
		touch = false;
		changed |= mode.released(display.touchX, display.touchY);
	}

	if (changed) display.fillScreen(RGB565_WHITE);

	topbar.draw();
	if (changed) {
		mode.draw();
	}
	display.flush();
}

