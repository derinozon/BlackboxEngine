#pragma once

#include <typeinfo>
#include <vector>

#include "../include/DG/DG_misc.h"

#include "mesh.h"

namespace ENG {
	
	inline std::string resFolder = std::string(DG_GetExecutableDir()) + "res/";
	
	namespace Resources {
		
		std::string Load (const char* path);
		Texture* LoadTexture (const char* path);

	}
}