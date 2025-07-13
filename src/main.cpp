#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <WiFi.h>

#include "network.h"
#include "display.h"
#include "topbar.h"
#include "horloge.h"

#include "const.h"

#include "USB.h"
#include "USBHIDKeyboard.h"


Network network;
Display display;
Horloge horloge;
TopBar topbar(display, horloge, network);

USBHIDKeyboard Keyboard;

void setup() {
	Serial.begin(115200);

	display.init();
	display.fillScreen(RGB565_LIGHTGREY);
	display.drawCenterText(160, 240, "Starting...", RGB565_BLACK);
	display.flush();

	network.init();
	horloge.init();

	//	Keyboard.begin();
	// USB.begin();

}

bool k = false;
void loop() {

	display.fillScreen(RGB565_LIGHTGREY);
	topbar.draw();

	if (display.isTouched()) {
		display.drawCenterText(160, 240, String(display.touchX) + "," + String(display.touchY), RGB565_BLACK);
		if (k) {
			Keyboard.println("bonjour");
		} else {
			USB.begin();
			Keyboard.begin();
			k = true;
		}
	}

	display.flush();

	delay(5);
}

