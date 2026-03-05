
#include "homeiot.h"

HomeIot::HomeIot() {

}

void HomeIot::init() {
	this->server = new WebServer(80);
	this->server->on(UriBraces("/captor/{}"), HTTP_PUT, [&](void) {this->receiveCaptorValue();});
	this->server->on(UriBraces("/captor/{}"), HTTP_POST, [&](void) {this->receiveCaptorValue();});
	this->server->begin();
}

void HomeIot::update() {
	this->server->handleClient();
}

void HomeIot::registerCaptor(uint16_t captor) {
	String url = HOST_CAPTOR + String(captor) + String("/register");
	if (http.begin(client, url)) {
		http.POST("");
		Serial.println(http.getString());
		http.end();
	}
}

void HomeIot::receiveCaptorValue() {
	int captor = server->pathArg(0).toInt();
	String value = server->arg("plain");
	Serial.print(captor);
	Serial.print(" Receive ");
	Serial.println(value);
	captors[captor] = value;
	this->server->send(200, "text/plain", "OK");
}

void HomeIot::setCaptor(uint16_t captor, String value) {
	if (http.begin(client, HOST_CAPTOR + String(captor))) {
		if (http.POST(value) == 202) {

		}
		http.end();
	}
}

String HomeIot::getCaptor(uint16_t captor) {
	auto it = captors.find(captor);
	if (it == captors.end()) {
		String r = "";
		if (http.begin(client, HOST_CAPTOR + String(captor))) {
			if (http.GET() == 202) {
				r = http.getString();
			}
			http.end();
		}
		return r;
	} else {
		return it->second;
	}
}

float_t HomeIot::getCaptorF(uint16_t captor) {
	float_t r = 0;
	if (http.begin(client, HOST_CAPTOR + String(captor))) {
		if (http.GET() == 202) {
			r = http.getString().toFloat();
		}
		http.end();
	}
	return r;
};

float_t HomeIot::getHaF(String captor) {
	float_t r = 0;
	String url = HOST_HA + captor;
	if (http.begin(client, url)) {
		int status = http.GET();
		if (status == 202) {
			r = http.getString().toFloat();
		}
		http.end();
	}
	return r;
};

float_t HomeIot::getHaF(String captor, String attr) {
	float_t r = 0;
	String url = HOST_HA + captor + "/" + attr;
	if (this->http.begin(this->client, url)) {
		int status = this->http.GET();
		if (status == 202) {
			r = this->http.getString().toFloat();
		}
		this->http.end();
	}
	return r;
};
