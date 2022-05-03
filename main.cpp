#include "src/editor.h"

using namespace ENG;
using namespace glm;

Entity* crate () {
	Entity* ent = CreateQuad("Crate");
	
	ent->transform = {vec3(0, 0, -1.5), vec3(0,0,45), vec3(3,3,3)};
	ent->material = Material("crate.png");
	return ent;
}

Entity* load3d (const char* modelPath, const char* texturePath) {
	Assimp::Importer importer;
	std::string inputFile = resFolder + modelPath;
	const aiScene *scene = importer.ReadFile(inputFile, aiProcess_Triangulate);
	//const aiScene *scene = importer.ReadFile(inputFile, aiProcess_Triangulate | aiProcess_FlipUVs);

	Model m = processNode(scene->mRootNode ,scene);
	Entity* object = CreateQuad(modelPath);
	object->mesh = m.meshes[1];
	object->material = Material(texturePath);
	return object;
}

int main() {
	Window* window = ENG::init("Blackbox Engine");
	ImGuiIO& io = Editor::InitEditor(window);
	
	// load3d("fish/fish1.fbx", "fish/fish1_tex.png");

	// Entity* obj = load3d("Test.fbx", "crate.png");
	//Entity* obj = load3d("coral/coral.fbx", "coral/base.png");
	//obj->transform.rotation = vec3(-90,0,0);
	// obj->transform.scale = vec3(0.1,0.1,0.1);

	Entity* obj = crate();
	
	OnUpdate += []() {
		float speed = 10 * Time.deltaTime * (Input.GetKey(GLFW_KEY_LEFT_SHIFT) ? 4 : 1);
		
		camera.Position += speed * glm::vec3(1,0,0) * Input.GetAxisHorizontal();
		camera.Position += speed * glm::vec3(0,0,-1) * Input.GetAxisVertical();
		
		if (Input.GetKey(GLFW_KEY_SPACE)) {
			camera.Position += speed * glm::vec3(0,1,0);
		}
		if (Input.GetKey(GLFW_KEY_LEFT_CONTROL)) {
			camera.Position += speed * glm::vec3(0,-1,0);
		}

		//entityList[0]->transform.rotation.y += speed;
	};
	Editor::Render();
	ENG::run(window);
	
	return 0;
}