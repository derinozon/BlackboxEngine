// #include "../src/editor.h"
#include "../blackbox.h"
#include "../src/internal/res_UV.h"

using namespace Blackbox;
using namespace glm;

void Teapot () {
	auto teapot = CreateQuad("Teapot");
	teapot->transform.position.y -= 1.5;
	teapot->mesh = LoadObj(nullptr);
	// glPolygonMode(GL_FRONT_AND_BACK, true ? GL_LINE : GL_FILL);
	//teapot->material = Blackbox::Material("Shiba_DIF01.png");
	teapot->material.texture = new Texture(UV_png, UV_png_len, 4);
	float col = 20.0/255.0;
	clearColor = vec4(col, col, col, 1.0);

	OnUpdate += []() {
		entityList[0]->transform.rotation.y += 50 * Time.deltaTime;
	};
}