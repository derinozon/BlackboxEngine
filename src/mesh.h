#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "texture.h"

namespace Blackbox {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class Mesh {
		public:
			// mesh data
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			std::string resourceHandle;
			//std::vector<Texture>      textures;

			Mesh();
			Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
			~Mesh();

			void Draw(Shader &shader);

			void setupMesh();

		private:
			//  render data
			uint32_t VAO, VBO, EBO;
	};
}