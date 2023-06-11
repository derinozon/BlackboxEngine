#include "primitive.h"

namespace Blackbox {

	ECS::Entity* CreateQuad (ECS::World* world) {
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

		ECS::Entity* ent = world->create();
		ent->assign<Transform>();
		ent->assign<Mesh>(pvertices, pindices);
		ent->assign<Material>();
		return ent;
	}
}