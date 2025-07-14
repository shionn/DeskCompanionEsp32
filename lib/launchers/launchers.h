#include <Arduino.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

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
	USBHIDKeyboard Keyboard;
	Display* display;
	bool initialized = false;
	t_shortcut shortcuts[5][4] = {
		{ { homer, "firefox http://homer/"}, { firefox, "firefox" }, { NULL, ""}, { discord, "discord" } },
		{ { terminal, "x-terminal-emulator"}, { NULL, "" }, { eclipse, "eclipse" }, { vscode, "code" } },
		{ { NULL, ""}, { NULL, "" }, { NULL, "" }, { NULL, "" } },
		{ { openscad, "openscad"}, { cura, "cura" }, { NULL, "" }, { gimp, "gimp" } },
		{ { steam, "steam"}, { heroic, "heroic" }, { lutris, "lutris" }, { minecraft, "minecraft-launcher" } }
	};

public:
	Launchers(Display* display);

	void draw();
	bool touched(uint16_t touchX, uint16_t touchy);

private:
	void drawicon(uint16_t x, uint16_t y, const uint16_t* icon);
	String toLocalFr(String cmd);
};

#endif
