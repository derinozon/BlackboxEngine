#include "../src/editor.h"
#include "res_dvd.h"

using namespace Blackbox;
using namespace glm;

vec3 vel = vec3(1,1,0);

void DVD () {
	auto dvd = CreateQuad("DVD");
	dvd->material.texture = new Texture(DVD_png, DVD_png_len);
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
	};
}