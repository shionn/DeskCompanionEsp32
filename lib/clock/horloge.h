
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <WiFi.h>

#ifndef __HORLOGE_H__
#define __HORLOGE_H__

#define NTP_PACKET_SIZE 48
#define NTP_LOCAL_PORT 8888


class Horloge {
private:
	int timezone = 2;
public:
	void init();

	int getHour();
	int getMinute();
	int getSecond();


};

#endif
