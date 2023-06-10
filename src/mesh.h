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

	struct Mesh {
		public:
			// mesh data
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			std::string resourceHandle;

			Mesh();
			Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
			~Mesh();

			void setupMesh();

			uint32_t VAO, VBO, EBO;
	};
}