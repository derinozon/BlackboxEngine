#include "engine.h"

using namespace ENG;
using namespace glm;

void crate () {
	Texture* brickTex2 = Resources::Load<Texture>("crate.png");
	Entity* ent = new Entity();
	
	ent->transform = {vec3(0, 0, -10), vec3(0,0,45), vec3(3,3,3)};
	ent->mesh = Mesh(pvertices, pindices);
	ent->material = Material(defaultShader, brickTex2);

	entityList.push_back(ent);
}

int main() {
	Window* window = ENG::init();
	crate();
	
	GameLoop = []() {
		float speed = 10.0f * Time.deltaTime;
		
		camera.Position += speed * glm::vec3(1,0,0) * Input.GetAxisHorizontal();
		camera.Position += speed * glm::vec3(0,0,-1) * Input.GetAxisVertical();
		if (Input.GetKey(GLFW_KEY_SPACE)) {
			camera.Position += speed * glm::vec3(0,1,0);
		}
		if (Input.GetKey(GLFW_KEY_LEFT_CONTROL)) {
			camera.Position += speed * glm::vec3(0,-1,0);
		}
	};
	ENG::run(window);
	
	return 0;
}