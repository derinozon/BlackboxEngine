// #include "demos/dvd.h"
#include "demos/teapot.h"
// #include "demos/particle.h"

int main() {
	Engine* engine = new Engine();
	Window* window = engine->init("Blackbox Engine");
	ImGuiIO& io = Editor::InitEditor(engine);

	return engine->run(window);
}