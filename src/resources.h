#pragma once

#include <typeinfo>
#include <vector>

#ifndef __EMSCRIPTEN__
#include "../include/DG/DG_misc.h"
#endif

#include "texture.h"

namespace Blackbox {
	
	#ifndef __EMSCRIPTEN__
	inline std::string resFolder = std::string(DG_GetExecutableDir()) + "res/";
	#else
	inline std::string resFolder = std::string("./res/");
	#endif

	namespace Resources {
		
		std::string ReadFile(std::string filePath);
		std::string Load (const char* path);
		Texture* LoadTexture (const char* path);

	}
}