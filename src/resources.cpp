#include "resources.h"

namespace ENG {
	namespace Resources {
		
		std::string Load (const char* path) {
			std::string out;
			std::ifstream infile(resFolder+path);
			infile >> out;
			infile.close();
			return out;
		}

		Texture* LoadTexture (const char* path) {
			return new Texture((resFolder+path).c_str());
		}

	}
}
