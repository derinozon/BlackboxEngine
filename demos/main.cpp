// #include "demos/dvd.h"
#include "teapot.h"
#include "particle.h"

Engine* engine;

int main() {
	engine = new Engine();
	Window* window = engine->init("Blackbox Engine");
	// ImGuiIO& io = Editor::InitEditor(engine);
		
	ParticleECS(engine);
	// Teapot(engine);

	engine->run(window);
	delete engine;
	return 0;
}