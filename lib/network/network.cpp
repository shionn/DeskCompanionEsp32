
#include "network.h"

void Network::init() {
	WiFi.disconnect(true);
	WiFi.mode(WIFI_STA);
	WiFi.setHostname("DeskCompanion");
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	WiFi.begin(SSID_NAME, SSID_PASS);
}

bool Network::connected() {
	
	return WiFi.status() == WL_CONNECTED;
}