// #include "demos/dvd.h"
#include "demos/teapot.h"

int main() {
	Window* window = Blackbox::init("Blackbox Engine");
	
	// ImGuiIO& io = Editor::InitEditor(window);
	
	Teapot();
	// DVD(window);
	
	return Blackbox::run(window);
}