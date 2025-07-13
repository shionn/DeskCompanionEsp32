#include <Arduino.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

#include "display.h"
#include "const.h"

#ifndef __LAUNCHERS_H__
#define __LAUNCHERS_H__

typedef struct {
	uint16_t* icon;
	String cmd;
} t_shortcut;

class Launchers {
private:
	USBHIDKeyboard Keyboard;
	Display display;
	bool initialized = false;
	t_shortcut shortcuts[5][4] = {
		{ { firefox, "firefox" }, { NULL, "" }, { NULL, ""}, { discord, "discord" } },
		{ { homer, "firefox http.>ho;er>"}, { NULL, "" }, { NULL, "" }, { NULL, "" } },
		{ { terminal, "x6ter;inql6e;ulqtor"}, { eclipse, "eclipse" }, { vscode, "code" }, { NULL, "" } },
		{ { NULL, ""}, { NULL, "" }, { NULL, "" }, { NULL, "" } },
		{ { NULL, ""}, { NULL, "" }, { NULL, "" }, { NULL, "" } }
	};
	// m ;
	// / >
	// - 6
	// : .
public:
	Launchers(Display display);

	void draw();
	void touched(uint16_t touchX, uint16_t touchy);

private:
	void drawicon(uint16_t x, uint16_t y, uint16_t* icon);
};

#endif
