// #include "demos/dvd.h"
// #include "demos/teapot.h"
#include "demos/particle.h"

int main() {
	Window* window = Blackbox::init("Blackbox Engine");
	// ImGuiIO& io = Editor::InitEditor(window);
	
	Particle();
	return Blackbox::run(window);
}