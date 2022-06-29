#include "src/editor.h"
#include "include/tiny_gltf_loader.h"


using namespace Blackbox;
using namespace glm;

void LoadGLTF () {
	tinygltf::Scene scene; 
	tinygltf::TinyGLTFLoader loader;
	std::string err;
	
	bool ret = loader.LoadASCIIFromFile(&scene, &err, "res/BoxTextured.gltf");
	auto m = scene.meshes.at(0).name.c_str();
	
	
	Entity* ent = CreateQuad(m);
	// ent->mesh = Mesh(scene.meshes.at(0));
}

void loadOBJFile () {
	auto teapot = CreateQuad("Teapot");
	teapot->mesh = LoadObj(nullptr);
	teapot->material = Blackbox::Material("Shiba_DIF01.png");
}

Entity* crate () {
	Entity* ent = CreateQuad("Crate");
	
	ent->transform = {vec3(0, 0, -1.5), vec3(0,0,45), vec3(3,3,3)};
	ent->material = Blackbox::Material("crate.png");
	return ent;
}

void loadbg () {
	auto quad = CreateQuad();
	auto path = resFolder+"bg.jpg";
	quad->material = Blackbox::Material(path.c_str());
	quad->transform.scale = vec3(10.75, 10.75, 1);
}

int main() {
	Window* window = Blackbox::init("Blackbox Engine");
	ImGuiIO& io = Editor::InitEditor(window);

	//Entity* obj = crate();
	//load_model();
	// LoadObj();

	#ifdef LITE
	
	#else
	// loadbg();
	#endif
	// CreateQuad();
	loadOBJFile();

	OnUpdate += []() {
		float speed = 10 * Time.deltaTime * (Input.GetKey(GLFW_KEY_LEFT_SHIFT) ? 4 : 1);
		
		camera.Position += speed * glm::vec3(1,0,0) * Input.GetAxisHorizontal();
		camera.Position += speed * glm::vec3(0,0,-1) * Input.GetAxisVertical();
		
		if (Input.GetKey(GLFW_KEY_E)) {
			camera.Position += speed * glm::vec3(0,1,0);
		}
		if (Input.GetKey(GLFW_KEY_Q)) {
			camera.Position += speed * glm::vec3(0,-1,0);
		}

		//entityList[0]->transform.rotation.y += speed;
	};
	Editor::Render();
	Blackbox::run(window);
	
	return 0;
}