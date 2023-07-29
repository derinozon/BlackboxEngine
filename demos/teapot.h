#include "../src/editor.h"
#include "../blackbox.h"
#include "../src/internal/res_UV.h"

using namespace Blackbox;
using namespace glm;

Engine* asdf;

void Teapot (Engine* engine) {
	asdf = engine;

	auto teapot = engine->world->create();
	teapot->assign<Transform>()->position.y -= 1.5;
	auto mdl = LoadObj(std::istringstream(TEAPOT_MODEL));
	teapot->assign<Mesh>(mdl.vertices, mdl.indices);
	// glPolygonMode(GL_FRONT_AND_BACK, true ? GL_LINE : GL_FILL);
	//teapot->material = Blackbox::Material("Shiba_DIF01.png");
	teapot->assign<Material>()->texture = new Texture(UV_png, UV_png_len, 4);
	float col = 20.0/255.0;
	engine->clearColor = vec4(col, col, col, 1.0);

	engine->OnUpdate += [](){
		if (asdf->Input.GetKey(GLFW_KEY_K)) {
			Log(asdf->camera->width, asdf->camera->height);
		}
	};
}