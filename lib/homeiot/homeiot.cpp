
#include "homeiot.h"

void HomeIot::init() {

};

float_t HomeIot::getCaptorF(uint16_t captor) {
	float_t r = -1;
	if (this->http.begin(this->client, HOST_CAPTOR + String(captor))) {
		if (this->http.GET() == 202) {
			r = this->http.getString().toFloat();
		}
		this->http.end();
	}
	return r;
};
