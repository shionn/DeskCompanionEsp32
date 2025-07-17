
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

Dashboard dashboard(&display, &homeiot);
Launchers launchers(&display, &storage);
Drawer drawer(&display);
Config config(&display);
Mode mode(&dashboard, &launchers, &drawer, &display, &config);
TopBar topbar(&display, &horloge, &network, &mode);

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
	if (mode.get() != 2) display.fillScreen(RGB565_WHITE);

	dashboard.update();
	if (display.isTouched()) {
		touch = true;
		mode.pressed(display.touchX, display.touchY);
	} else if (touch) {
		touch = false;
		mode.released(display.touchX, display.touchY);
	}

	topbar.draw();
	mode.draw();

	display.flush();
}

