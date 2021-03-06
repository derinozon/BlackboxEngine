#include "src/editor.h"

using namespace Blackbox;
using namespace glm;

void loadOBJFile () {
	auto teapot = CreateQuad("Teapot");
	teapot->mesh = LoadObj(nullptr);
	teapot->material = Blackbox::Material("Shiba_DIF01.png");
}

int main() {
	Window* window = Blackbox::init("Blackbox Engine");
	ImGuiIO& io = Editor::InitEditor(window);

	loadOBJFile();

	OnUpdate += []() {
		entityList[0]->transform.rotation.y += 10 * Time.deltaTime;
	};
	Editor::Render();
	Blackbox::run(window);
	
	return 0;
}