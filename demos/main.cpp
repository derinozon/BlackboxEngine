// #include "demos/dvd.h"
// #include "teapot.h"
// #include "particle.h"
#include "platformer.h"

int main() {
	Configuration conf;
	Engine engine = Engine();
	Window* window = engine.init(conf);
	// ImGuiIO& io = Editor::InitEditor(engine);

	// engine->OnUpdate += [](){
	// 	Log("Camera width is ", engine->camera->width);
	// };

	// ParticleECS(engine);
	// Teapot(engine);

	Platformer(&engine);

	return engine.run(window);
}