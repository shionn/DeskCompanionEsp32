#include "dashboard.h"

Dashboard::Dashboard(Display display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
}

void Dashboard::draw() {
	this->display.drawCenterText(160, 30, "Temperature O11dw", RGB565_BLACK);
	this->drawTempBar(50, "Cpu", this->cpu, 0, 90);
	this->drawTempBar(72, "Gpu", this->gpu, 0, 90);
	this->drawTempBar(94, "Nvme", this->nvme, 0, 90);
	this->display.drawCenterText(160, 120, "Maison", RGB565_BLACK);
	this->drawTempBar(140, "Exterieur", this->exterior, 0, 50);
	this->drawTempBar(162, "Bureau", this->office, 0, 50);
	this->drawTempBar(184, "Morgan", this->bedroom, 0, 50);
	this->drawElecBar(206, "Consso.", this->elec_consso, 0, 6);
	this->drawElecBar(228, "Prod.", this->elec_prod, 0, 6);


}

void Dashboard::drawTempBar(uint16_t y, String text, float_t value, uint16_t min, uint16_t max) {
	uint16_t color = RGB565_ORANGE;
	if (value - min <= (max - min) / 2) {
		color = RGB565_DARKGREEN;
	}
	if (value - min >= 3 * (max - min) / 4) {
		color = RGB565_RED;
	}
	this->display.fillRect(10, y, map(value, min, max, 0, 300), 20, color);
	this->display.drawText(12, y + 2, text, RGB565_BLACK);
	this->display.drawRightText(308, y + 2, String(value, 1) + "c", RGB565_BLACK);
	this->display.drawRect(10, y, 300, 20, RGB565_BLACK);
}

void Dashboard::drawElecBar(uint16_t y, String text, float_t value, float_t min, float_t max) {
	uint16_t color = RGB565_ORANGE;
	if (value - min <= (max - min) / 2) {
		color = RGB565_DARKGREEN;
	}
	if (value - min >= 3 * (max - min) / 4) {
		color = RGB565_RED;
	}
	this->display.fillRect(10, y, map(value * 1000, min * 1000, max * 1000, 0, 300), 20, color);
	this->display.drawText(12, y + 2, text, RGB565_BLACK);
	this->display.drawRightText(308, y + 2, String(value, 3) + "kw", RGB565_BLACK);
	this->display.drawRect(10, y, 300, 20, RGB565_BLACK);
}


void Dashboard::update() {
	if (!cpu || millis() > lastUpdated + 60 * 1000) {
		lastUpdated = millis();
		this->cpu = iot->getCaptorF(111);
		this->gpu = iot->getCaptorF(110);
		this->nvme = iot->getCaptorF(112);
		this->office = iot->getCaptorF(100);
		this->bedroom = iot->getCaptorF(101);
		this->elec_consso = iot->getHaF("sensor.envoy_122333059807_consommation_electrique_actuelle");
		this->elec_prod = iot->getHaF("sensor.envoy_122333059807_production_d_electricite_actuelle");
		this->exterior = iot->getHaF("weather.forecast_maison", "temperature");
	}
};
