#include "resources.h"
#include "debug.h"

namespace Blackbox {
	namespace Resources {

		std::string ReadFile(std::string filePath) {
			std::ifstream file(resFolder+filePath);
			if (!file) {
				LogError("Failed to open file : ", filePath);
				return "";
			}

			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();

			return buffer.str();
		}

		Texture* LoadTexture (const char* path) {
			Texture* tex = new Texture((resFolder+path).c_str());
			return tex;
		}

	}
}
