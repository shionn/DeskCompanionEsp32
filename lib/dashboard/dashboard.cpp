#include "dashboard.h"

Dashboard::Dashboard(Display* display, HomeIot* iot) {
	this->display = display;
	this->iot = iot;
}

void Dashboard::draw() {
	int y = 30;
	this->display->drawCenterText(160, y, "Temperature O11dw", RGB565_BLACK);
	this->drawTempBar(y += 20, "Cpu", this->cpu, 0, 90);
	this->drawTempBar(y += 22, "Gpu E", this->gpuEdge, 0, 90);
	this->drawTempBar(y += 22, "Gpu J", this->gpuJunc, 0, 90);
	this->drawTempBar(y += 22, "Nvme", this->nvme, 0, 90);
	this->drawWattBar(y += 22, "Consso.", this->pc_consso, 0, 700);
	this->display->drawCenterText(160, y += 30, "Maison", RGB565_BLACK);
	this->drawTempBar(y += 20, "Exterieur", this->exterior, 0, 50);
	this->drawTempBar(y += 22, "Bureau", this->office, 0, 50);
	this->drawTempBar(y += 22, "Morgan", this->bedroom, 0, 50);
	this->drawElecBar(y += 22, "Prod.", this->elec_prod, 0, 6);
	this->drawElecBar(y += 22, "Consso.", this->elec_consso, 0, 6);
	this->drawWattBar(y += 22, "Home Lab", this->hl_consso, 0, 700);


}

void Dashboard::drawTempBar(uint16_t y, String text, float_t value, uint16_t min, uint16_t max) {
	this->drawValueBar(y, text, value, min, max, 1, "c");
}

void Dashboard::drawElecBar(uint16_t y, String text, float_t value, float_t min, float_t max) {
	this->drawValueBar(y, text, value, min, max, 3, "kw");
}

void Dashboard::drawWattBar(uint16_t y, String text, float_t value, float_t min, float_t max) {
	this->drawValueBar(y, text, value, min, max, 1, "w");
}

void Dashboard::drawValueBar(uint16_t y, String text, float_t value, float_t min, float_t max, unsigned int decimal, String unit) {
	uint16_t color = RGB565_ORANGE;
	if (value - min <= (max - min) / 2) {
		color = RGB565_DARKGREEN;
	}
	if (value - min >= 3 * (max - min) / 4) {
		color = RGB565_RED;
	}
	this->display->fillRoundRect(10, y, 300, 20, 3, RGB565_LIGHTGREY);
	this->display->fillRoundRect(10, y, map(value, min, max, 0, 300), 20, 3, color);
	this->display->drawText(13, y + 3, text, RGB565_BLACK);
	this->display->drawRightText(307, y + 3, String(value, decimal) + unit, RGB565_BLACK);
	this->display->drawRoundRect(10, y, 300, 20, 3, RGB565_BLACK);
}

bool Dashboard::update() {
	if (!cpu || millis() > lastUpdated + 60 * 1000) {
		lastUpdated = millis();
		this->cpu = iot->getCaptorF(111);
		this->gpuEdge = iot->getCaptorF(110);
		this->gpuJunc = iot->getCaptorF(114);
		this->nvme = iot->getCaptorF(112);
		this->office = iot->getCaptorF(100);
		this->bedroom = iot->getCaptorF(101);
		this->elec_consso = iot->getHaF("sensor.envoy_122333059807_consommation_electrique_actuelle");
		this->elec_prod = iot->getHaF("sensor.envoy_122333059807_production_d_electricite_actuelle");
		this->pc_consso = iot->getHaF("sensor.desk_plug_puissance");
		this->hl_consso = iot->getHaF("sensor.homelab_plug_puissance");
		this->exterior = iot->getHaF("weather.forecast_maison", "temperature");

		return true;
	}
	return false;
};

boolean Dashboard::pressed(uint16_t touchX, uint16_t touchY) { return false; }
boolean Dashboard::released(uint16_t touchX, uint16_t touchY) { return false; }
