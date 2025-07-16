
#include "storage.h"

void Storage::init() {
	SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
	SD_MMC.begin("/sdmmc", true, false, 20000);
}

uint16_t* Storage::readSprite(const char* filename) {
	File file = SD_MMC.open(filename);
	uint16_t* result;
	if (file) {
		uint8_t header[54];
		file.read(header, 54);
		uint16_t w = *(int*)&header[18];
		uint16_t h = *(int*)&header[22];

		if (*(short*)&header[28] == 24) {
			result = this->readBmp24(file, w, h);
		}
		file.close();
	}
	return result;
}

uint16_t* Storage::readBmp24(File file, uint16_t w, uint16_t h) {
	uint16_t* buffer = new uint16_t[w * h + 2];
	buffer[0] = w;
	buffer[1] = h;
	file.seek(54);
	uint16_t rowSize = (w * 3 + 3) & ~3; // Row size must be a multiple of 4
	uint8_t rowBuffer[rowSize];
	for (int y = h - 1;y >= 0;y--) {
		file.read(rowBuffer, rowSize);
		for (int x = 0;x < w;x++) {
			uint8_t b = rowBuffer[x * 3];     // Blue
			uint8_t g = rowBuffer[x * 3 + 1]; // Green
			uint8_t r = rowBuffer[x * 3 + 2]; // Red
			buffer[y * w + x + 2] = RGB565(r, g, b);
			// buffer[y * w + x] = bmpFile.read() << 8 | bmpFile.read();
		}
	}
	return buffer;
}




