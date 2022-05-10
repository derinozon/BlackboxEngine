// Usefull definitions //
#include "src/def.h"
#include "blackbox.h"

namespace Blackbox {
	
	Window* init (const char* title, int width, int height, bool fullscreen, bool vsync) {
		// Initialize GLFW
		glfwSetErrorCallback([](int error, const char *msg){
			std::cerr << '[' << error << ']' << msg << std::endl;
		});
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "Init success" << std::endl;
		
		#ifdef __EMSCRIPTEN__
		// emscripten_get_canvas_size()
		#endif
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

		std::cout << "Viewport success" << std::endl;

		GLFWdropfun drop_callback = [] (GLFWwindow* window, int count, const char** paths) {
			const char* name = paths[0];
			Entity* ent = CreateQuad(name);
			ent->material.texture = new Texture(paths[0]);
		};

		glfwSetDropCallback(window->Get(), drop_callback);

		camera.perspective = true;

		defaultShader = new Shader(
			DEFAULT_UNLIT_VERT,
			DEFAULT_UNLIT_FRAG
		);

		currentWindow = window;
		return window;
	}

	
	int run (Window* window) {
		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);

		

		auto loop = []{
			Input.SetWindow(currentWindow->Get());

			// Calculate deltatime //
			Time.time = glfwGetTime();
			Time.deltaTime = Time.time - Time.lastFrameTime;
			Time.lastFrameTime = Time.time;
			
			// Enable blending //
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			// Clean the back buffer and depth buffer //
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.UpdateMatrix();
			OnUpdate.Invoke();

			// Draw Meshes //
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
				glm::vec3 finalPos = tr.position;
				
				model = glm::translate(model, finalPos);

				model = glm::rotate(model, glm::radians(tr.rotation.x), glm::vec3(1,0,0));
				model = glm::rotate(model, glm::radians(tr.rotation.y), glm::vec3(0,1,0));
				model = glm::rotate(model, glm::radians(tr.rotation.z), glm::vec3(0,0,1));
				model = glm::scale(model, tr.scale);
				
				if (mat.texture->width != mat.texture->height) {
					double w = (double)(mat.texture->width);
					double h = (double)(mat.texture->height);
					double d = w > h ? w : h;
					model = glm::scale(model, glm::vec3(w/d, h/d, 1.0) );
				}

				if (mat.shader != nullptr) {
					mat.shader->UploadUniformMatrix4fv("_MVP", camera.projection * camera.view * model);
				}

				vel.Draw(*mat.shader);
			}
			OnDrawGUI.Invoke();
			

			glfwSwapBuffers(currentWindow->Get());
			glfwPollEvents();
		};

		
		#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(loop, 0, 1);
		#else
		while (!glfwWindowShouldClose(window->Get())) {
			loop();
		}
		#endif
		
		for (Entity* obj: entityList) {
			delete obj;
		};

		OnQuit.Invoke();

		glfwDestroyWindow(window->Get());
		glfwTerminate();
		return 0;
	}
}