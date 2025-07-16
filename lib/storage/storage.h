
#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <Arduino.h>
#include <Arduino_GFX.h>
#include <SD_MMC.h>


#define SD_MMC_D0 13
#define SD_MMC_CLK 12
#define SD_MMC_CMD 11

class Storage {

public:
	void init();

	const uint16_t* readSprite(const char* file);
private:
	uint16_t* readBmp24(File bmpFile, uint16_t w, uint16_t h);
	uint16_t* readBmp16(File bmpFile, uint16_t w, uint16_t h);
};


#endif
