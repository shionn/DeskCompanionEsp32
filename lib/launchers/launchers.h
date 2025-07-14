#include <Arduino.h>
#include <USB.h>
#include <USBHIDKeyboard.h>
// #include <BleKeyboard.h>

#include "display.h"
#include "const.h"

#ifndef __LAUNCHERS_H__
#define __LAUNCHERS_H__

typedef struct {
	const uint16_t* icon;
	String cmd;
} t_shortcut;

class Launchers {
private:
	// BleKeyboard keyboard;
	USBHIDKeyboard keyboard;
	Display* display;
	bool initialized = false;
	t_shortcut shortcuts[5][4] = {
		{ { homer, F("firefox http://homer/")}, { firefox, F("firefox") }, { NULL, ""}, { discord, F("discord") } },
		{ { terminal, F("x-terminal-emulator")}, { NULL, "" }, { eclipse, F("eclipse") }, { vscode, F("code") } },
		{ { NULL, ""}, { NULL, "" }, { NULL, "" }, { NULL, "" } },
		{ { openscad, F("openscad")}, { cura, F("cura") }, { NULL, "" }, { gimp, F("gimp") } },
		{ { steam, F("steam")}, { heroic, F("heroic") }, { lutris, F("lutris") }, { minecraft, F("minecraft-launcher") } }
	};

public:
	Launchers(Display* display);

	void init();
	void draw();
	bool touched(uint16_t touchX, uint16_t touchy);

private:
	void drawicon(uint16_t x, uint16_t y, const uint16_t* icon);
	String toLocalFr(String cmd);
};

#endif
