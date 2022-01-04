#include "../lib/ImGUI/imgui.h"
#include "../lib/ImGUI/imgui_impl_glfw.h"
#include "../lib/ImGUI/imgui_impl_opengl3.h"

#include "editor.h"

void InitEditor (Window* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}