
#ifndef __HOME_IOT_H__
#define __HOME_IOT_H__

#include <Arduino.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include <unordered_map>

#define HOST_CAPTOR "http://homeiot/captor/"
#define HOST_HA "http://homeiot/ha/"

class HomeIot {
private:
	WiFiClient client;
	HTTPClient http;
	std::unordered_map<int, String> captors;

public:
	HomeIot();
	void init();
	void update();

	void registerCaptor(uint16_t captor);
	void setCaptor(uint16_t captor, String value);
	String getCaptor(uint16_t captor);

	float_t getCaptorF(uint16_t captor);
	float_t getHaF(String captor);
	float_t getHaF(String captor, String attr);

private:
	void receiveCaptorValue();
	// void receiveCaptorValue(AsyncWebServerRequest* request, String data);

};

#endif