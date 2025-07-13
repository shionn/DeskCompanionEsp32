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

#include "const.h"

Network network;
HomeIot homeiot;
Horloge horloge;
Display display;

TopBar topbar(display, horloge, network);

Launchers launchers(display);

void setup() {
	Serial.begin(115200);

	display.init();
	display.fillScreen(RGB565_LIGHTGREY);
	display.drawCenterText(160, 240, "Starting...", RGB565_BLACK);
	display.flush();

	network.init();
	homeiot.init();
	horloge.init();

	//	Keyboard.begin();
	// USB.begin();

}

bool k = false;
void loop() {

	display.fillScreen(RGB565_LIGHTGREY);
	topbar.draw();
	launchers.draw();

	// display.drawCenterText(160, 240, String(homeiot.getCaptorF(100), 1), RGB565_BLACK);

	if (display.isTouched()) {
		launchers.touched(display.touchX, display.touchY);
		// 	display.drawCenterText(160, 240, String(display.touchX) + "," + String(display.touchY), RGB565_BLACK);
		// 	// if (k) {
		// 	// 	Keyboard.println("bonjour");
		// 	// } else {
		// 	// 	USB.begin();
		// 	// 	Keyboard.begin();
		// 	// 	k = true;
		// 	// }
		while (display.isTouched()) delay(1);
		delay(100);
	}

	display.flush();

	delay(5);
}

