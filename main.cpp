// #include "demos/dvd.h"
#include "demos/teapot.h"
#include "demos/particle.h"

Engine* engine;




int main() {
	engine = new Engine();
	Window* window = engine->init("Blackbox Engine");
	ImGuiIO& io = Editor::InitEditor(engine);
	
	ParticleECS(engine);


	engine->OnUpdate += []{
	};

	engine->run(window);
	delete engine;
	return 0;
}