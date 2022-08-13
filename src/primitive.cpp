#include "primitive.h"

namespace Blackbox {

	Entity* CreateQuad (const char* label) {
		// Indices for vertices order
		std::vector<unsigned int> pindices = {
			0, 1, 2,
			2, 0, 3
		};

		std::vector<Vertex> pvertices = {
			// positions          // colors           // texture coords
			{glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(1.0f, 1.0f)},   // top right
			{glm::vec3(0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(1.0f, 0.0f)},   // bottom right
			{glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(0.0f, 0.0f)},   // bottom left
			{glm::vec3(-0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(0.0f, 1.0f)}    // top left 
		};

		Entity* ent = new Entity(label);
		ent->mesh = Mesh(pvertices, pindices);
		ent->mesh.resourceHandle = "QUAD";
		return ent;
	}
	Entity* CreateQuad () {
		return CreateQuad("Quad");
	}
}