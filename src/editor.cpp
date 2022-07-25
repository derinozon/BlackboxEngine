#include "editor.h"

namespace Blackbox::Editor {
	bool wireframe;
	bool vsync = true;
	int selectedObj = -1;

	ImGuiIO& InitEditor (Window* window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);
		#ifdef __EMSCRIPTEN__
		ImGui_ImplOpenGL3_Init("#version 300 es");
		#else
		ImGui_ImplOpenGL3_Init("#version 330");
		#endif

		auto Debug = []() {
			ImGui::Begin("Debug");
			std::string fps = "FPS : " + std::to_string( (int)(1.0/Time.deltaTime) );
			ImGui::Text("%s", fps.c_str());
			
			if (ToggleField("Vsync", &vsync) ) {
				glfwSwapInterval(vsync);
			}
			#ifndef __EMSCRIPTEN__
			if (ToggleField("Wireframe", &wireframe) ) {
				glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
			}
			#endif
			ImGui::End();
		};

		auto Hierarchy = []() {
			ImGui::Begin("Hierarchy");
			if (ImGui::BeginPopupContextWindow()) {
				if (ImGui::MenuItem("New Entity")) {
					CreateQuad();
				}

				ImGui::EndPopup();
			}
			for (int i = 0; i < entityList.size(); i++) {
				if ( ImGui::Selectable((entityList[i]->name + "##" +std::to_string(i)).c_str(), i==selectedObj) ) {
					selectedObj = i;
				}
			}
			ImGui::End();
		};
		
		auto Inspector = []() {
			ImGui::Begin("Inspector");
			if (selectedObj > -1) {
				Entity* obj = entityList[selectedObj];

				obj->transform.position = Editor::DragFloat3("Position", obj->transform.position);
				obj->transform.rotation = Editor::DragFloat3("Rotation", obj->transform.rotation, 0.5);
				obj->transform.scale = Editor::DragFloat3("Scale", obj->transform.scale);

				obj->material.color = Editor::ColorField("Color", obj->material.color);
				
				Editor::Label("Image");
				Editor::ImageField(obj->material.texture);
			}
			ImGui::End();
		};

		OnUpdate += []() {
			// Deleting objects on backspace or delete key //
			#ifdef __APPLE__
			bool cmd = (Input.GetKey(GLFW_KEY_LEFT_SUPER)||Input.GetKey(GLFW_KEY_RIGHT_SUPER))&&Input.GetKey(GLFW_KEY_BACKSPACE);
			#else
			bool cmd = Input.GetKey(GLFW_KEY_DELETE);
			#endif
			if (cmd && selectedObj>-1) {
				delete entityList[selectedObj];
				selectedObj = -1;
			}

			// Editor Camera movement //
			float speed = 10 * Time.deltaTime * (Input.GetKey(GLFW_KEY_LEFT_SHIFT) ? 4 : 1);
		
			camera.Position += speed * glm::vec3(1,0,0) * Input.GetAxisHorizontal();
			camera.Position += speed * glm::vec3(0,0,-1) * Input.GetAxisVertical();
			
			if (Input.GetKey(GLFW_KEY_E)) {
				camera.Position += speed * glm::vec3(0,1,0);
			}
			if (Input.GetKey(GLFW_KEY_Q)) {
				camera.Position += speed * glm::vec3(0,-1,0);
			}
		};

		OnDrawGUI += []() {
			NewFrame();
		};

		OnDrawGUI += Debug;
		OnDrawGUI += Hierarchy;
		OnDrawGUI += Inspector;

		Log("Editor Initialized");

		// io.Fonts->AddFontFromFileTTF("./res/Roboto-Light.ttf", 12);
		ImGuiStyle& style = ImGui::GetStyle();
		
		// io.DisplaySize = ImVec2(1600*2, 900*2);
		// style.ScaleAllSizes(0.1);

		return io;
	}

	void DestroyEditor () {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	// Call this once
	void Render () {
		OnDrawGUI += []() {
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		};
		OnQuit += []() {
			Log("Destroying Editor");
			Editor::DestroyEditor();
		};
	}

	void NewFrame () {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Label (const char* label) {
		ImGui::LabelText(label, "");
	}

	void IntField (const char* label, int* val) {
		ImGui::InputInt(label, val);
	}

	bool ToggleField (const char* label, bool* val) {
		return ImGui::Checkbox(label, val);
	}

	void ImageField (Texture* texture) {
		ImGui::Image((void*)(intptr_t)(texture->ID), {80, 80}, {0,1}, {1,0});
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