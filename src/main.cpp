#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <WiFi.h>

#include "const.h"

// Pin definitions
#define GFX_BL 1
#define TOUCH_ADDR 0x3B
#define TOUCH_SDA 4
#define TOUCH_SCL 8
#define TOUCH_I2C_CLOCK 400000
#define TOUCH_RST_PIN 12
#define TOUCH_INT_PIN 11
#define AXS_MAX_TOUCH_NUMBER 1

Arduino_DataBus* bus = new Arduino_ESP32QSPI(45, 47, 21, 48, 40, 39);
Arduino_GFX* g = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, 320, 480);
Arduino_Canvas* gfx = new Arduino_Canvas(320, 480, g, 0, 0, 0);

uint16_t touchX, touchY;

void setup() {
	Serial.begin(115200);

	// Initialize Display
	gfx->begin();

	// Initialize touch
	Wire.begin(TOUCH_SDA, TOUCH_SCL);
	Wire.setClock(TOUCH_I2C_CLOCK);

	// Configure touch pins
	pinMode(TOUCH_INT_PIN, INPUT_PULLUP);
	pinMode(TOUCH_RST_PIN, OUTPUT);
	digitalWrite(TOUCH_RST_PIN, LOW);
	delay(200);
	digitalWrite(TOUCH_RST_PIN, HIGH);
	delay(200);


	gfx->setRotation(2);
	gfx->fillScreen(RGB565_BLUE);
	pinMode(GFX_BL, OUTPUT);  //Back Light On
	digitalWrite(GFX_BL, HIGH);
	gfx->setTextSize(2);
	gfx->setTextColor(RGB565_GREEN);
	gfx->setCursor(100, 10);
	gfx->print("Bonjour Shionn");
	// gfx->dra
	gfx->flush();

	gfx->draw16bitRGBBitmapWithTranColor(0, 0, mimic + 2, RGB565(255, 0, 255), mimic[0], mimic[1]);
	// gfx->draw16bitRGBBitmap(0, 0, mimic + 2, mimic[2], mimic[0], mimic[1]);
	// gfx->draw16bitRGBBitmap(0, 100, rgb + 2, rgb[0], rgb[1]);
	gfx->flush();

	WiFi.disconnect(true);
	WiFi.mode(WIFI_STA); //Optional
	WiFi.setAutoConnect(true);
	WiFi.begin("AsusHome_5G", "foobarqix");
	if (WiFi.status() == WL_CONNECTED) {
		gfx->setCursor(0, 450);
		gfx->print(WiFi.localIP().toString());
		gfx->flush();
	}


	// SPI.begin(GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_11, GPIO_NUM_10);
	// if (SD.begin(GPIO_NUM_10)) {
	// 	if (SD.cardType() != CARD_NONE) {
	// 		gfx->setCursor(0, 0);
	// 		gfx->print("SD");
	// 		gfx->flush();



			// JPEGDecoder decoder;
			// decoder.decodeFile("pic/mimic.jpg");
			// gfx->setCursor(0, 0);
			// gfx->print(decoder.);
			// gfx->flush();

			// gfx->draw16bitRGBBitmap(0, 0, decoder.pImage, decoder.width, decoder.height);
			// gfx->flush();
		// }

	// }


}

bool getTouchPoint(uint16_t& x, uint16_t& y) {
	uint8_t data[AXS_MAX_TOUCH_NUMBER * 6 + 2] = { 0 };

	// Define the read command array properly
	const uint8_t read_cmd[11] = {
		0xb5, 0xab, 0xa5, 0x5a, 0x00, 0x00,
		(uint8_t)((AXS_MAX_TOUCH_NUMBER * 6 + 2) >> 8),
		(uint8_t)((AXS_MAX_TOUCH_NUMBER * 6 + 2) & 0xff),
		0x00, 0x00, 0x00
	};

	Wire.beginTransmission(TOUCH_ADDR);
	Wire.write(read_cmd, 11);
	if (Wire.endTransmission() != 0) return false;

	if (Wire.requestFrom(TOUCH_ADDR, sizeof(data)) != sizeof(data)) return false;

	for (int i = 0; i < sizeof(data); i++) {
		data[i] = Wire.read();
	}

	if (data[1] > 0 && data[1] <= AXS_MAX_TOUCH_NUMBER) {
		uint16_t rawX = ((data[2] & 0x0F) << 8) | data[3];
		uint16_t rawY = ((data[4] & 0x0F) << 8) | data[5];
		if (rawX > 500 || rawY > 500) return false;
		x = map(rawX, 0, 320, 320, 0);
		y = map(rawY, 0, 480, 480, 0);
		return true;
	}
	return false;
}



int status = 0;

void loop() {
	if (getTouchPoint(touchX, touchY)) {
		gfx->fillRect(100, 100, 200, 20, RGB565_BLUE);
		gfx->setCursor(100, 100);
		gfx->print(String(touchX) + "," + String(touchY));
		gfx->drawCircle(touchX, touchY, 2, RGB565_WHITE);
		gfx->flush();
	}

	if (WiFi.status() != status) {
		status = WiFi.status();
		if (status == WL_CONNECTED) {
			gfx->setCursor(0, 400);
			gfx->print(status);
			gfx->print(WiFi.localIP().toString());
			gfx->flush();
		}
	}
	delay(5);
}

