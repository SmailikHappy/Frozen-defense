#pragma once

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

void Log(int var, bool state = true) {
	std::cout << var;
	if (state) {
		std::cout << std::endl;
	}
}
void Log(std::string var, bool state = true) {
	std::cout << var;
	if (state) {
		std::cout << std::endl;
	}
}
void Log(float var, bool state = true) {
	std::cout << var;
	if (state) {
		std::cout << std::endl;
	}
}
void Log(double var, bool state = true) {
	std::cout << var;
	if (state) {
		std::cout << std::endl;
	}
}
void Log(short var, bool state = true) {
	std::cout << var;
	if (state) {
		std::cout << std::endl;
	}
}
void Log(char var, bool state = true) {
	std::cout << var;
	if (state) {
		std::cout << std::endl;
	}
}
void Log(char* var, bool state = true) {

	for (int i = 0; i < (sizeof(*var) / sizeof(var[0])); i++) {
		std::cout << var;
	}
	
	if (state) {
		std::cout << std::endl;
	}
}

#endif // !DEBUG