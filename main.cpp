#include "src/editor.h"

using namespace Blackbox;
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
	object->mesh = m.meshes[0];
	object->material = Material(texturePath);
	return object;
}

void load3ds (const char* modelPath, const char* texturePath, float scale = 0.1f) {
	Assimp::Importer importer;
	std::string inputFile = resFolder + modelPath;
	const aiScene *scene = importer.ReadFile(inputFile, aiProcess_Triangulate);
	//const aiScene *scene = importer.ReadFile(inputFile, aiProcess_Triangulate | aiProcess_FlipUVs);

	SeriousModel(scene->mRootNode ,scene, scale);	
}

void loadStatic (const char* modelPath, const char* texturePath, float scale = 0.1f) {
	Assimp::Importer importer;
	std::string inputFile = resFolder + modelPath;
	const aiScene *scene = importer.ReadFile(inputFile, aiProcess_Triangulate);
	//const aiScene *scene = importer.ReadFile(inputFile, aiProcess_Triangulate | aiProcess_FlipUVs);

	StaticModel(scene->mRootNode ,scene, scale);	
}

void wip () {
	// load3ds("Test2.fbx", "crate.png", 1);
	// loadStatic("Test2.fbx", "crate.png");

	Entity* obj = load3d("coral/coral.fbx", "coral/base.png");
	obj->transform.rotation = vec3(-90,0,0);
	obj->transform.scale = vec3(0.1,0.1,0.1);
}

int main() {
	Window* window = Blackbox::init("Blackbox Engine");
	ImGuiIO& io = Editor::InitEditor(window);

	// Entity* obj = crate();
	wip();

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
	Blackbox::run(window);
	
	return 0;
}