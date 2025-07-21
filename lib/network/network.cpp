
#include "network.h"

void Network::init() {
	WiFi.disconnect(true);
	WiFi.setHostname("DeskCompanion");
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	WiFi.begin(SSID_NAME, SSID_PASS);
	while (!WiFi.isConnected()) {
		Serial.print(".");
		delay(100);
	}
	Serial.println();
	Serial.print("Connected. Ip: ");
	Serial.println(WiFi.localIP().toString());
}

bool Network::connected() {

	return WiFi.status() == WL_CONNECTED;
}