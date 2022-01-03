#include <glm/glm.hpp>

class Color {
	public:
		unsigned char r, g, b, a;

		// float* ToFloatArray () {
		// 	// float arr[4] = {r/255.0, g/255.0, b/255.0, a/255.0};
		// 	float arr[4] = {
		// 		static_cast<float>(r/255.0),
		// 		static_cast<float>(g/255.0),
		// 		static_cast<float>(b/255.0),
		// 		static_cast<float>(a/255.0)
		// 	};
		// 	return arr;
		// }

		glm::vec4 ToVector () {
			return glm::vec4(r/255.0, g/255.0, b/255.0, a/255.0);
		}

		Color operator=(const glm::vec4& v) {
			// return {
			// 	(unsigned char)(v.x*255),
			// 	(unsigned char)(v.y*255),
			// 	(unsigned char)(v.z*255),
			// 	(unsigned char)(v.w*255)
			// };

			return {
				static_cast<unsigned char>(r*255.0),
				static_cast<unsigned char>(g*255.0),
				static_cast<unsigned char>(b*255.0),
				static_cast<unsigned char>(a*255.0)
			};
		}
};