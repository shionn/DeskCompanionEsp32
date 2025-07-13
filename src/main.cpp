#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <WiFi.h>

#include "network.h"
#include "display.h"
#include "topbar.h"
#include "horloge.h"
#include "homeiot.h"
#include "launchers.h"
#include "mode.h"
#include "dashboard.h"

Network network;
HomeIot* homeiot = new HomeIot();
Horloge horloge;
Display display;

Mode mode(display);
TopBar topbar(display, horloge, network);
Launchers launchers(display);
Dashboard dashboard(display, homeiot);


void setup() {
	Serial.begin(115200);

	display.init();
	display.fillScreen(RGB565_LIGHTGREY);
	display.drawCenterText(160, 240, "Starting...", RGB565_BLACK);
	display.flush();

	network.init();
	horloge.init();

}

void loop() {

	display.fillScreen(RGB565_LIGHTGREY);
	topbar.draw();
	switch (mode.get()) {
	default:
	case 0:
		dashboard.draw();
		break;
	case 1:
		launchers.draw();
		break;
	}
	mode.draw();

	dashboard.update();

	if (display.isTouched()) {
		switch (mode.get()) {
		case 1:
			launchers.touched(display.touchX, display.touchY);
			break;
		}
		mode.touched(display.touchX, display.touchY);
		while (display.isTouched()) delay(10);
	}
	display.flush();
	delay(5);
}

