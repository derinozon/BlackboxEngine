#include <iostream>

// Usefull definitions //
#include "src/def.h"
#include "engine.h"


bool vsync = true;

namespace ENG {

	// Camera camera(1600, 900, glm::vec3(0.0f, 0.1f, 0.0f));

	Window* init () {
		// Initialize GLFW
		glfwSetErrorCallback([](int error, const char *msg){
			std::cerr << '[' << error << ']' << msg << std::endl;
		});
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "Init success" << std::endl;
		
		Window* window = new Window(1600, 900, false);
		
		
		
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
		glViewport(0, 0, width, height);
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

		auto loop = []{
			Input.SetWindow(currentWindow->Get());
			// CALCULATING DELTATIME //
			Time.time = glfwGetTime();
			Time.deltaTime = Time.time - Time.lastFrameTime;
			Time.lastFrameTime = Time.time;

			// std::cout << (Time.deltaTime) << std::endl;
			
			

			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			// Clean the back buffer and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.UpdateMatrix();

			// (*OnUpdate)();
			// OnUpdate();

			// Draw Meshes
			for (Entity* obj: entityList) {
				Transform& tr = obj->transform;
				Mesh& vel = obj->mesh;
				Material& mat = obj->material;
				
				// if (mat.shader == nullptr) mat.shader = defaultShader;
				// if (mat.texture == nullptr) mat.texture = Resources::Load<Texture>(mat.texturePath.c_str());

				mat.shader->Activate();
				mat.shader->UploadUniform1i("tex0", 0);
				mat.texture->Bind();
				
				// Generate Model Matrix from Transform //
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, tr.position);
				model = glm::rotate(model, tr.rotation.x, glm::vec3(1,0,0));
				model = glm::rotate(model, tr.rotation.y, glm::vec3(0,1,0));
				model = glm::rotate(model, tr.rotation.z, glm::vec3(0,0,1));
				model = glm::scale(model, tr.scale);

				mat.shader->UploadUniformMatrix4fv("_MVP", camera.projection * camera.view * model);

				vel.Draw(*mat.shader);
			}
			GameLoop();
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
		glfwDestroyWindow(window->Get());
		glfwTerminate();
		return 0;
	}
}