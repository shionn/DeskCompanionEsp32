#include "dashboard.h"

Dashboard::Dashboard(Display display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
}

void Dashboard::draw() {
	this->display.drawCenterText(160, 30, "Temperature O11dw", RGB565_BLACK);
	this->drawTemperatue(50, "Cpu  ", this->cpu, 0, 90);
	this->drawTemperatue(70, "Gpu  ", this->gpu, 0, 90);
	this->drawTemperatue(90, "Nvme ", this->nvme, 0, 90);
	this->display.drawCenterText(160, 115, "Temperature Maison", RGB565_BLACK);
	this->drawTemperatue(135, "Desk ", this->office, 0, 50);
	this->drawTemperatue(155, "Bed  ", this->bedroom, 0, 50);

}

void Dashboard::drawTemperatue(uint16_t y, String text, uint16_t value, uint16_t min, uint16_t max) {
	uint16_t color = RGB565_ORANGE;
	if (value - min <= (max - min) / 2) {
		color = RGB565_DARKGREEN;
	}
	if (value - min >= 3 * (max - min) / 4) {
		color = RGB565_RED;
	}
	this->display.drawText(5, y, text + String(value), RGB565_BLACK);
	this->display.fillRect(100, y, map(value, min, max, 0, 210), 16, color);
	this->display.getGfx()->drawRect(100, y, 210, 16, RGB565_BLACK);
}

void Dashboard::update() {
	if (!cpu || millis() > lastUpdated + 60 * 1000) {
		lastUpdated = millis();
		this->cpu = (uint16_t)iot->getCaptorF(111);
		this->gpu = (uint16_t)iot->getCaptorF(110);
		this->nvme = (uint16_t)iot->getCaptorF(112);
		this->office = (uint16_t)iot->getCaptorF(100);
		this->bedroom = (uint16_t)iot->getCaptorF(101);
	}
};
