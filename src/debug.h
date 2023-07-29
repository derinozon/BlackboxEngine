#pragma once

#include <iostream>

#ifndef BLACKBOX_DEBUG
	#define BLACKBOX_DEBUG 1
#endif

namespace Blackbox {

	#if BLACKBOX_DEBUG == 1
	template<class... Args>
	static void Log (Args... args) {
		(std::cout << ... << args) << std::endl;
	}

	static void Log (const char* msg) {
		std::cout << msg << std::endl;
	}
	#else
	template<class... Args>
	static void Log (Args... args){}

	static void Log (const char* msg){}
	#endif
}