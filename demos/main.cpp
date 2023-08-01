// #include "demos/dvd.h"
// #include "teapot.h"
#include "particle.h"
// #include "platformer.h"

int main() {
	Engine* engine;
	Configuration conf;
	engine = new Engine();
	Window* window = engine->init(conf);
	// ImGuiIO& io = Editor::InitEditor(engine);

	// engine->OnUpdate += [](){
	// 	Log("Camera width is ", engine->camera->width);
	// };

	ParticleECS(engine);
	// Teapot(engine);

	// Platformer(engine);

	engine->run(window);
	delete engine;
	return 0;
}