#include "InputOutput.hpp"

void Input::changeValue() {
	/*if (value == 1)
		value = 0;
	else
		value = 1;*/
	value = !value;
}

string Input::formatName() const {
	if (name.find(" ") != string::npos)
		return ("(" + name + ")");
	else
		return name;
}
