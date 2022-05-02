#include "engine.h"

// #include "tiny_obj_loader.h"
// #include <unordered_map>

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
	object->mesh = m.meshes[0];
	object->material = Material(texturePath);
	return object;
}

bool wireframe;
bool vsync = true;
int main() {
	Window* window = ENG::init("Blackbox Engine");
	
	// crate();
	
	
	
	OnDrawGUI.Add( []() {
		ImGui::Begin("Debug");
		std::string fps = "FPS : " + std::to_string( (int)(1.0/Time.deltaTime) );
		Editor::Label(fps.c_str());
		if (Editor::ToggleField("Vsync", &vsync) ) {
			glfwSwapInterval(vsync ? 60 : 0);
		}
		if (Editor::ToggleField("Wireframe", &wireframe) ) {
			glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
		}
		ImGui::End();
	} );
	//load3d("fish/fish1.fbx", "fish/fish1_tex.png");
	Entity* obj = load3d("coral/coral.fbx", "coral/base.png");
	//Entity* obj = crate();
	obj->transform.rotation = vec3(-90,0,0);
	obj->transform.scale = vec3(0.1,0.1,0.1);
	
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

		//entityList[0]->transform.rotation.y += speed;
	};
	ENG::run(window);
	
	return 0;
}