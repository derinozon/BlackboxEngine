#include "engine.h"

using namespace ENG;
using namespace glm;

void crate () {
	Texture* crateTex = Resources::Load<Texture>("crate.png");
	Entity* ent = CreateQuad("Crate");
	
	ent->transform = {vec3(0, 0, -1), vec3(0,0,45), vec3(3,3,3)};
	ent->material = Material(defaultShader, crateTex);
}

void box () {
	Entity* ent = CreateQuad("Box");
}

int main() {
	#ifdef WIN
	resFolder = "C:\\Users\\admin\\Documents\\Github\\BlackboxEngine\\res\\";
	#endif
	Window* window = ENG::init("Blackbox Engine");
	crate();
	
	//box();
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