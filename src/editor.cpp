#include "editor.h"

namespace Blackbox::Editor {
	bool wireframe;
	bool vsync = true;
	int selectedObj = -1;
	Engine* engine;

	ImGuiIO& InitEditor (Engine* eng) {
		engine = eng;
		Window* window = eng->currentWindow;

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

		engine->OnUpdate += []() {
			// Deleting objects on backspace or delete key //
			#ifdef __APPLE__
			bool cmd = (engine->Input.GetKey(GLFW_KEY_LEFT_SUPER)||engine->Input.GetKey(GLFW_KEY_RIGHT_SUPER))&&engine->Input.GetKey(GLFW_KEY_BACKSPACE);
			#else
			bool cmd = engine->Input.GetKey(GLFW_KEY_DELETE);
			#endif
			if (cmd && selectedObj>-1) {
				delete engine->world->getByIndex(selectedObj);
				selectedObj = -1;
			}

			// Editor Camera movement //
			float speed = 10 * Time.deltaTime * (engine->Input.GetKey(GLFW_KEY_LEFT_SHIFT) ? 4 : 1);
		
			engine->camera->Position += speed * glm::vec3(1,0,0) * engine->Input.GetAxisHorizontal();
			engine->camera->Position += speed * glm::vec3(0,0,-1) * engine->Input.GetAxisVertical();
			
			if (engine->Input.GetKey(GLFW_KEY_E)) {
				engine->camera->Position += speed * glm::vec3(0,1,0);
			}
			if (engine->Input.GetKey(GLFW_KEY_Q)) {
				engine->camera->Position += speed * glm::vec3(0,-1,0);
			}
		};

		engine->OnQuit += []() {
			Log("Destroying Editor");
			Editor::DestroyEditor();
		};

		engine->OnDrawGUI += []() {
			NewFrame();

			if (renderEditor) {
				Render();
			}
		
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		};

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

	void Render () {
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
					CreateQuad(engine->world);
				}

				ImGui::EndPopup();
			}
			for (int i = 0; i < engine->world->getCount(); i++) {
				if ( ImGui::Selectable((engine->world->getByIndex(i)->getEntityId() + "##" +std::to_string(i)).c_str(), i==selectedObj) ) {
					selectedObj = i;
				}
			}
			ImGui::End();
		};
		
		auto Inspector = []() {
			ImGui::Begin("Inspector");
			if (selectedObj > -1) {
				ECS::Entity* obj = engine->world->getByIndex(selectedObj);
				auto objTransform = obj->get<Transform>();
				auto objMat = obj->get<Material>();

				objTransform->position = Editor::DragFloat3("Position", objTransform->position);
				objTransform->rotation = Editor::DragFloat3("Rotation", objTransform->rotation, 0.5);
				objTransform->scale = Editor::DragFloat3("Scale", objTransform->scale);

				objMat->color = Editor::ColorField("Color", objMat->color);
				
				Editor::Label("Image");
				Editor::ImageField(objMat->texture);
			}
			ImGui::End();
		};

		Debug();
		Hierarchy();
		Inspector();
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