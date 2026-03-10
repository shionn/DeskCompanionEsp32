
#include "color.h"

uint32_t Color::hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
	h = map(h,0,65535,0,60000);
	int r = 0, g = 0, b = 0;

	switch (h / 10000) {
	case 0:
		r = 255;
		g = map(h, 0, 10000, 0, 255);
		break;
	case 1:
		r = map(h, 10000, 20000, 255, 0);
		g = 255;
		break;
	case 2:
		g = 255;
		b = map(h, 20000, 30000, 0, 255);
		break;
	case 3:
		g = map(h, 30000, 40000, 255, 0);
		b = 255;
		break;
	case 4:
		r = map(h, 40000, 50000, 0, 255);
		b = 255;
		break;
	case 5:
		r = 255;
		b = map(h, 50000, 60000, 255, 0);
		break;
	}
	r = map(s, 0, 255, 255, r);
	g = map(s, 0, 255, 255, g);
	b = map(s, 0, 255, 255, b);

	r = map(v, 0, 255, 0, r);
	g = map(v, 0, 255, 0, g);
	b = map(v, 0, 255, 0, b);

	return r>>16 | b>>8 | g;
}

uint16_t Color::hsvToRgb565(uint16_t h, uint8_t s, uint8_t v) {
	h = map(h, 0, 65535, 0, 60000);
	int r = 0, g = 0, b = 0;

	switch (h / 10000) {
	case 0:
		r = 255;
		g = map(h, 0, 10000, 0, 255);
		break;
	case 1:
		r = map(h, 10000, 20000, 255, 0);
		g = 255;
		break;
	case 2:
		g = 255;
		b = map(h, 20000, 30000, 0, 255);
		break;
	case 3:
		g = map(h, 30000, 40000, 255, 0);
		b = 255;
		break;
	case 4:
		r = map(h, 40000, 50000, 0, 255);
		b = 255;
		break;
	case 5:
		r = 255;
		b = map(h, 50000, 60000, 255, 0);
		break;
	}
	r = map(s, 0, 255, 255, r);
	g = map(s, 0, 255, 255, g);
	b = map(s, 0, 255, 255, b);

	r = map(v, 0, 255, 0, r);
	g = map(v, 0, 255, 0, g);
	b = map(v, 0, 255, 0, b);
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
};

String Color::hsvToString(uint16_t h, uint8_t s, uint8_t v) {
	char buffer[9];  
	snprintf(buffer, sizeof(buffer), "%04X%02X%02X", h, s, v);
	return buffer;
};

uint16_t Color::stringToHue(String str) {
	return strtoul(str.c_str(), NULL, 16) >> 16 & 0xFFFF;
};

uint8_t Color::stringToSat(String str) {
	return strtoul(str.c_str(), NULL, 16) >> 8 & 0xFF;
};

uint8_t Color::stringToValue(String str) {
	return strtoul(str.c_str(), NULL, 16) & 0xFF;
};

