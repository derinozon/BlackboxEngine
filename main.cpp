#include "src/editor.h"
#include "src/internal/res_dvd.h"

using namespace Blackbox;
using namespace glm;

void Teapot () {
	auto teapot = CreateQuad("Teapot");
	teapot->mesh = LoadObj(nullptr);
	teapot->material = Blackbox::Material("Shiba_DIF01.png");

	OnUpdate += []() {
		entityList[0]->transform.rotation.y += 10 * Time.deltaTime;
	};
}

vec3 vel = vec3(1,1,0);
void DVD () {
	auto dvd = CreateQuad("DVD");
	// dvd->material = Material("DVD.png");
	dvd->material.texture = Texture(DVD_png)

	camera.perspective = false;

	OnUpdate += []() {
		entityList[0]->transform.position += vel * (float)Time.deltaTime;
		float w = 0.5;
		float h = 0.285;
		
		if (entityList[0]->transform.position.y+h > camera.bounds.w) {
			vel.y = -1;
		}
		if (entityList[0]->transform.position.x+w > camera.bounds.y) {
			vel.x = -1;
		}
		if (entityList[0]->transform.position.y-h < camera.bounds.z) {
			vel.y = 1;
		}
		if (entityList[0]->transform.position.x-w < camera.bounds.x) {
			vel.x = 1;
		}

		Log(vel.y);
	};
}

int main() {
	Window* window = Blackbox::init("Blackbox Engine");
	ImGuiIO& io = Editor::InitEditor(window);

	// Teapot();
	DVD();

	Editor::Render();
	Blackbox::run(window);
	
	return 0;
}