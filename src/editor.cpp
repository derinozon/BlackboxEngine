#include "editor.h"

namespace ENG::Editor {

	ImGuiIO& InitEditor (Window* window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO io = ImGui::GetIO(); (void)io;
		// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);
		#ifdef __EMSCRIPTEN__
		ImGui_ImplOpenGL3_Init("#version 300 es");
		#else
		ImGui_ImplOpenGL3_Init("#version 330");
		#endif
		return io;
	}

	void DestroyEditor () {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Render () {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void NewFrame () {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	glm::vec3 DragFloat3 (const char* label, glm::vec3 vec, float speed) {
		float arr[3] = {vec.x, vec.y, vec.z};
		ImGui::DragFloat3(label, arr, speed);
		return glm::vec3(arr[0], arr[1], arr[2]);
	};

	glm::vec4 ColorField (const char* label, glm::vec4 color) {
		float arr[4] = {color.x, color.y, color.z, color.w};
		ImGui::ColorEdit4(label, arr);
		return glm::vec4(arr[0], arr[1], arr[2], arr[3]);
	};
}