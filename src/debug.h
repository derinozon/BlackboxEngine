#pragma once

#include <iostream>

template<class... Args>
static void Log (Args... args) {
    (std::cout << ... << args) << std::endl;
}

static void Log (const char* msg) {
	std::cout << msg << std::endl;
}