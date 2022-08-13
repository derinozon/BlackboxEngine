#include "../src/editor.h"
#include "../src/internal/res_UV.h"

using namespace Blackbox;
using namespace glm;

void Teapot () {
	auto teapot = CreateQuad("Teapot");
	teapot->transform.position.y -= 1.5;
	teapot->mesh = LoadObj(nullptr);
	//teapot->material = Blackbox::Material("Shiba_DIF01.png");
	teapot->material.texture = new Texture(UV_png, UV_png_len, 4);

	OnUpdate += []() {
		entityList[0]->transform.rotation.y += 10 * Time.deltaTime;
	};
}