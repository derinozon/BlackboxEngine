#include "resources.h"
#include "debug.h"

namespace Blackbox {
	namespace Resources {

		std::string ReadFile(std::string filePath) {
			std::ifstream file(resFolder+filePath);
			if (!file) {
				// Handle file opening error
				// For example, you can throw an exception or return an empty string
				return "";
			}

			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();

			return buffer.str();
		}
		
		// std::string Load (const char* path) {
		// 	std::string out;
		// 	std::ifstream infile(resFolder+path);
		// 	infile >> out;
		// 	infile.close();
		// 	return out;
		// }

		Texture* LoadTexture (const char* path) {
			Texture* tex = new Texture((resFolder+path).c_str());
			return tex;
		}

	}
}
