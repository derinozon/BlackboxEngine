#pragma once

#include <vector>
#include <glm/glm.hpp>
// #include <nlohmann/json.hpp>

#include "texture.h"
#include "serialization.h"

namespace ENG {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;

		// NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vertex, Position, Normal, TexCoords)
	};

	class Mesh {
		public:
			// mesh data
			std::vector<Vertex>       vertices;
			std::vector<unsigned int> indices;
			std::string resourceHandle;
			//std::vector<Texture>      textures;

			Mesh();
			Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
			~Mesh();

			void Draw(Shader &shader);

			void setupMesh();

			// NLOHMANN_DEFINE_TYPE_INTRUSIVE(Mesh, resourceHandle)

		private:
			//  render data
			unsigned int VAO, VBO, EBO;
	};
}