#include "../src/editor.h"
#include "res_dvd.h"
#include <glm/gtc/random.hpp>

using namespace Blackbox;
using namespace glm;

Entity* dvd;
vec3 vel = vec3(1,1,0);
vec2 bounds;

vec2 Bounds (Entity* ent) {
	float w = 1, h = 1;
	Texture* tex = ent->material.texture;

	if (tex->width >= tex->height) {
		h = (float)tex->height/tex->width;
	}
	if (tex->width < tex->height) {
		w = (float)tex->width/tex->height;
	}

	return vec2(w, h) * (vec2)ent->transform.scale;
}

void DVD (Window* window) {
	Editor::renderEditor = false;
	window->MakeFullscreen();
	clearColor = vec4(0,0,0,0);

	dvd = CreateQuad("DVD");
	dvd->transform.scale *= (float)2.5;
	dvd->material.texture = new Texture(DVD_png, DVD_png_len);
	dvd->material.color = vec4(0,0,1,1);
	camera.perspective = false;

	bounds = Bounds(dvd);

	OnUpdate += []() {
		dvd->transform.position += vel * (float)(Time.deltaTime * 5);
		float w = bounds.x/2;
		float h = bounds.y/2;
		
		auto col = [](vec4 prev) {
			srand(time(0));
			int v[3] = { rand()&1, rand()&1, rand()&1 };
			if (v[0]+v[1]+v[2] == 0)
				v[rand()%3] = 1;
			if (v[0]+v[1]+v[2] == 3)
				v[rand()%3] = 0;
			
			vec4 ret = vec4(v[0], v[1], v[2], 1);
			if (ret == prev)
				ret = vec4(v[1], v[2], v[0], 1);

			return ret;
		};
		
		if (dvd->transform.position.y+h > camera.bounds.w) {
			vel.y = -1;
			dvd->material.color = col(dvd->material.color);
		}
		if (dvd->transform.position.x+w > camera.bounds.y) {
			vel.x = -1;
			dvd->material.color = col(dvd->material.color);
		}
		if (dvd->transform.position.y-h < camera.bounds.z) {
			vel.y = 1;
			dvd->material.color = col(dvd->material.color);
		}
		if (dvd->transform.position.x-w < camera.bounds.x) {
			vel.x = 1;
			dvd->material.color = col(dvd->material.color);
		}
	};
}