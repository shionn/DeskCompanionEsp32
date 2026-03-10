#ifndef __COLOR_H__
#define __COLOR_H__

#include <Arduino.h>

class Color {

public :
	static uint32_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v);
	static uint16_t hsvToRgb565(uint16_t h, uint8_t s, uint8_t v);
	static String hsvToString(uint16_t h, uint8_t s, uint8_t v);

	static uint16_t stringToHue(String str);
	static uint8_t stringToSat(String str);
	static uint8_t stringToValue(String str);
};

#endif
