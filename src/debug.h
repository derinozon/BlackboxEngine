#pragma once

#include <iostream>

namespace Blackbox {

    static char LOG_INFO = 1;
	static char LOG_ERRORS = 2;
    static char LOG_INTERNAL = 4;
	static unsigned char debugFlags = LOG_INFO | LOG_ERRORS;

	template<class... Args>
	static void Log (Args... args) {
		if ((debugFlags & LOG_INFO) == LOG_INFO) {
			(std::cout << ... << args) << std::endl;
		}
	}

	template<class... Args>
	static void LogError (Args... args) {
		if ((debugFlags & LOG_ERRORS) == LOG_ERRORS) {
			(std::cout << ... << args) << std::endl;
		}
	}

	template<class... Args>
	static void LogInternal (Args... args) {
		if ((debugFlags & LOG_INTERNAL) == LOG_INTERNAL) {
			(std::cout << ... << args) << std::endl;
		}
	}
}