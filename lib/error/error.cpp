#include "error.h"

LastError::LastError() {
}

void LastError::set(String source, String content) {
	this->source = source;
	this->content = content;
}

String LastError::getContent() {
	return this->content;
}

String LastError::getSource() {
	return this->source;
}
