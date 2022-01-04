#include <iostream>

// Usefull definitions //
#include "src/def.h"
#include "engine.h"


bool vsync = true;
int selectedObj = -1;

namespace ENG {

	// Camera camera(1600, 900, glm::vec3(0.0f, 0.1f, 0.0f));
	
	// void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
    // 	glViewport(0, 0, width, height);
	// 	camera.width = width;
	// 	camera.height = height;
	// }

	
	Window* init (const char* title, int width, int height, bool fullscreen) {
		// Initialize GLFW
		glfwSetErrorCallback([](int error, const char *msg){
			std::cerr << '[' << error << ']' << msg << std::endl;
		});
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "Init success" << std::endl;
		
		Window* window = new Window(title, width, height, fullscreen);
		
		if (window->Get() == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		
		std::cout << "Window success" << std::endl;

		glfwMakeContextCurrent(window->Get());
		std::cout << "Ctx success" << std::endl;
		
		//Load GLAD so it configures OpenGL
		#ifndef __EMSCRIPTEN__
			glfwSwapInterval(vsync);
			gladLoadGL();
		#endif

		auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			camera.width = width;
			camera.height = height;
		};

		glfwSetFramebufferSizeCallback(window->Get(), framebuffer_size_callback);
		framebuffer_size_callback(window->Get(), width, height);
		// glViewport(0, 0, width, height);
		std::cout << "Viewport success" << std::endl;
		camera.perspective = true;

		defaultShader = new Shader(
			(resFolder/fs::path("default.vert")).c_str(),
			(resFolder/fs::path("default.frag")).c_str()
		);

		// init_scripting();
		currentWindow = window;
		return window;
	}

	int run (Window* window) {

		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);
		ImGui_ImplOpenGL3_Init("#version 330");


		auto loop = []{
			Input.SetWindow(currentWindow->Get());
			// CALCULATING DELTATIME //
			Time.time = glfwGetTime();
			Time.deltaTime = Time.time - Time.lastFrameTime;
			Time.lastFrameTime = Time.time;
			
			// Enable blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			// Clean the back buffer and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			

			camera.UpdateMatrix();

			// (*OnUpdate)();
			// OnUpdate();
			GameLoop();

			// Draw Meshes
			for (Entity* obj: entityList) {
				Transform& tr = obj->transform;
				Mesh& vel = obj->mesh;
				Material& mat = obj->material;
				
				
				if (mat.shader == nullptr) mat.shader = defaultShader;
				if (mat.texture == nullptr) {
					unsigned char white[] = {255,255,255};
					mat.texture = new Texture(white, 1, 1, 3, GL_TEXTURE_2D);
				}
				
				mat.shader->Activate();
				mat.shader->UploadUniform4f("color", mat.color);
				if (mat.texture != nullptr) {
					mat.shader->UploadUniform1i("tex0", 0);
					mat.texture->Bind();
				}
				
				
				// Generate Model Matrix from Transform //
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, tr.position);
				model = glm::rotate(model, glm::radians(tr.rotation.x), glm::vec3(1,0,0));
				model = glm::rotate(model, glm::radians(tr.rotation.y), glm::vec3(0,1,0));
				model = glm::rotate(model, glm::radians(tr.rotation.z), glm::vec3(0,0,1));
				model = glm::scale(model, tr.scale);

				if (mat.shader != nullptr) {
					mat.shader->UploadUniformMatrix4fv("_MVP", camera.projection * camera.view * model);
				}

				vel.Draw(*mat.shader);
			}

			ImGui::Begin("Hierarch");
			for (int i = 0; i < entityList.size(); i++) {
				if ( ImGui::Selectable(entityList[i]->name.c_str(), i==selectedObj) ) {
					selectedObj = i;
				}
			}
			if (ImGui::Button("New Sprite")) {
				Entity* ent = new Entity("New Sprite");
				ent->mesh = Mesh(pvertices, pindices);
				entityList.push_back(ent);
			}
			ImGui::End();
			
			ImGui::Begin("Inspector");
			if (selectedObj > -1) {
				auto DragFloat3 = [](const char* label, glm::vec3 vec) {
					float vector[3] = {vec.x, vec.y, vec.z};
					ImGui::DragFloat3(label, vector, 0.05);
					return glm::vec3(vector[0], vector[1], vector[2]);
				};

				Entity* obj = entityList[selectedObj];

				obj->transform.position = DragFloat3("Position", obj->transform.position);
				obj->transform.rotation = DragFloat3("Rotation", obj->transform.rotation);
				obj->transform.scale = DragFloat3("Scale", obj->transform.scale);

				glm::vec4 vec = obj->material.color;
				float color[4] = {vec.x, vec.y, vec.z, vec.w};
				ImGui::ColorEdit4("Color", color);
				obj->material.color = glm::vec4(color[0], color[1], color[2], color[3]);
			}
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(currentWindow->Get());
			glfwPollEvents();
		};

		
		#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(loop, 0, 1);
		std::cout << "WEB" << std::endl;
		#else
		while (!glfwWindowShouldClose(window->Get())) {
			loop();
		}
		#endif
		
		for (Entity* obj: entityList) {
			delete obj;
		};
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window->Get());
		glfwTerminate();
		return 0;
	}
}