#ifndef __LAUNCHERS_H__
#define __LAUNCHERS_H__

#include <Arduino.h>
#include <USB.h>
#include <USBHIDKeyboard.h>
// #include <BleKeyboard.h>
// #include <Adafruit_TinyUSB.h>

#include "display.h"
#include "const.h"
#include "storage.h"



typedef struct {
	const uint16_t* icon;
	uint8_t key;
} t_shortcut;

class Launchers {
private:
	// BleKeyboard keyboard;
	USBHIDKeyboard keyboard;
	Display* display;
	Storage* storage;
	bool usbInitialized = false;
	bool initialized = false;
	// Adafruit_USBD_HID usb_hid;

#ifdef __SPRITE_FROM_FLASH__
	t_shortcut shortcuts[5][4] = {
		// F19 does not work
		{ { homer, KEY_F1}, { firefox, KEY_F2 }, { NULL, KEY_F3}, { discord, KEY_F4 } },
		{ { terminal, KEY_F5}, { NULL, KEY_F6 }, { eclipse, KEY_F7}, { vscode, KEY_F8 } },
		{ { NULL, KEY_F9}, { NULL, KEY_F10 }, { NULL, KEY_F11 }, { NULL, KEY_F12 } },
		{ { openscad, KEY_F13}, { cura, KEY_F14  }, { NULL, KEY_F15 }, { gimp, KEY_F16 } },
		{ { steam, KEY_F17}, { heroic, KEY_F18 }, { lutris, KEY_F20 }, { minecraft, KEY_F21 } }
	};
	// t_shortcut shortcuts[5][4] = {
	// 	// F19 does not work
	// 	{ { homer, HID_KEY_F1}, { firefox, HID_KEY_F2 }, { NULL, HID_KEY_F3}, { discord, HID_KEY_F4 } },
	// 	{ { terminal, HID_KEY_F5}, { NULL, HID_KEY_F6 }, { eclipse, HID_KEY_F7}, { vscode, HID_KEY_F8 } },
	// 	{ { NULL, HID_KEY_F9}, { NULL, HID_KEY_F10 }, { NULL, HID_KEY_F11 }, { NULL, HID_KEY_F12 } },
	// 	{ { openscad, HID_KEY_F13}, { cura, HID_KEY_F14  }, { NULL, HID_KEY_F15 }, { gimp, HID_KEY_F16 } },
	// 	{ { steam, HID_KEY_F17}, { heroic, HID_KEY_F18 }, { lutris, HID_KEY_F20 }, { minecraft, HID_KEY_F21 } }
// };
#else
	t_shortcut shortcuts[5][4] = {
		// F19 does not work
		{ { NULL, KEY_F1}, { NULL, KEY_F2 }, { NULL, KEY_F3}, { NULL, KEY_F4 } },
		{ { NULL, KEY_F5}, { NULL, KEY_F6 }, { NULL, KEY_F7}, { NULL, KEY_F8 } },
		{ { NULL, KEY_F9}, { NULL, KEY_F10 }, { NULL, KEY_F11 }, { NULL, KEY_F12 } },
		{ { NULL, KEY_F13}, { NULL, KEY_F14  }, { NULL, KEY_F15 }, { NULL, KEY_F16 } },
		{ { NULL, KEY_F17}, { NULL, KEY_F18 }, { NULL, KEY_F20 }, { NULL, KEY_F21 } }
	};
#endif

public:
	Launchers(Display* display, Storage* storage);

	void init();
	void draw();
	bool pressed(uint16_t touchX, uint16_t touchY);
	bool released(uint16_t touchX, uint16_t touchY);

private:
	void drawicon(uint16_t x, uint16_t y, const uint16_t* icon);
};

#endif
