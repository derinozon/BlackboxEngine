#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "texture.h"

namespace ENG {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class Mesh {
		public:
			// mesh data
			std::vector<Vertex>       vertices;
			std::vector<unsigned int> indices;
			//std::vector<Texture>      textures;

			Mesh();
			Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
			~Mesh();

			void Draw(Shader &shader);

			void setupMesh();

		private:
			//  render data
			unsigned int VAO, VBO, EBO;
	};
}