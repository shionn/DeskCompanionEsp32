#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <WiFi.h>

#include "dashboard.h"
#include "display.h"
#include "drawer.h"
#include "horloge.h"
#include "homeiot.h"
#include "launchers.h"
#include "topbar.h"
#include "mode.h"
#include "network.h"

Network network;
HomeIot homeiot;
Horloge horloge;
Display display;

Mode mode(&display);
TopBar topbar(&display, &horloge, &network, &mode);
Dashboard dashboard(&display, &homeiot);
Launchers launchers(&display);
Drawer drawer(&display);


void setup() {
	Serial.begin(115200);

	display.init();
	display.fillScreen(RGB565_WHITE);
	display.drawCenterText(160, 240, "Starting...", RGB565_BLACK);
	display.flush();

	network.init();
	horloge.init();

}

void loop() {
	if (mode.get() != 2) display.fillScreen(RGB565_WHITE);

	dashboard.update();
	boolean consummed = false;
	if (display.isTouched()) {
		switch (mode.get()) {
		case 1:
			consummed = launchers.touched(display.touchX, display.touchY);
			break;
		case 2:
			drawer.touched(display.touchX, display.touchY);
			break;
		}
		if (!consummed) {
			consummed = mode.touched(display.touchX, display.touchY);
		}
	}

	topbar.draw();
	switch (mode.get()) {
	default:
	case 0:
		dashboard.draw();
		break;
	case 1:
		launchers.draw();
		break;
	case 2:
		drawer.draw();
		break;
	}
	mode.draw();


	display.flush();
	if (consummed) {
		delay(300);
		while (display.isTouched()) delay(100);
	}
}

