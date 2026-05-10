#ifndef __ERROR_H__
#define __ERROR_H__

#include <Arduino.h>

class LastError {
private:
	String source = "";
	String content = "";
public:
	LastError();
	void set(String source, String content);

	String getSource();
	String getContent();
};

#endif
