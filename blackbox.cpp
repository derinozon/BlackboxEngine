#include "blackbox.h"

namespace Blackbox {

	#ifdef __EMSCRIPTEN__
	EMSCRIPTEN_KEEPALIVE int framebuffer_size_callback(int eventType, const EmscriptenUiEvent* uiEvent, void* userData) {
		// int width = uiEvent->windowInnerWidth;
		// int height = uiEvent->windowInnerHeight;
		// emscripten_get_canvas_element_size("canvas", &width, &height);
		double cw, ch;
		emscripten_get_element_css_size("canvas", &cw, &ch);
		int width = (int) cw;
		int height = (int) ch;

		glViewport(0, 0, width, height);
		camera.width = width;
		camera.height = height;
		return 0;
	}
	#endif
	// auto Engine::framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
	// 	glViewport(0, 0, width, height);
	// 	camera.width = width;
	// 	camera.height = height;
	// };
	Window* Engine::init (const char* title, int width, int height, bool fullscreen, bool vsync, bool resizable) {
		camera = Camera(1600, 900, glm::vec3(0.0f, 0.0f, 5.0f));
		clearColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
		
		// Initialize GLFW
		glfwSetErrorCallback([](int error, const char *msg){
			std::cerr << '[' << error << ']' << msg << std::endl;
		});
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, resizable);

		// glfwWindowHint(GLFW_DECORATED , 0);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER , 1);

		glfwWindowHint(GLFW_SAMPLES  , 8);
		glfwWindowHint(GLFW_SRGB_CAPABLE, 1);
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

		#ifdef __EMSCRIPTEN__
			// Work in progress not 
			emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, &framebuffer_size_callback);
		#else
			glfwSetFramebufferSizeCallback(window->Get(), framebuffer_size_callback);
			framebuffer_size_callback(window->Get(), width, height);
		#endif

		std::cout << "Viewport success" << std::endl;

		GLFWdropfun drop_callback = [] (GLFWwindow* window, int count, const char** paths) {
			const char* name = paths[0];
			Entity* ent = CreateQuad(name);
			ent->material.texture = new Texture(paths[0]);
		};

		glfwSetDropCallback(window->Get(), drop_callback);

		// glfwSetKeyCallback(window->Get(), Input.keyCallback);

		camera.perspective = true;

		defaultShader = new Shader(
			DEFAULT_UNLIT_VERT,
			DEFAULT_UNLIT_FRAG
		);

		currentWindow = window;
		world = ECS::World::createWorld();
		return window;
	}

	void Engine::loop (){
		Input.SetWindow(currentWindow->Get());

		// Calculate deltatime //
		Time.time = glfwGetTime();
		Time.deltaTime = Time.time - Time.lastFrameTime;
		Time.lastFrameTime = Time.time;
		
		// Enable blending //
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		// Clean the back buffer and depth buffer //
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.UpdateMatrix();
		OnUpdate.Invoke();
		world->tick(Time.deltaTime);

		// Draw Meshes //
		for (ECS::Entity* ent : world->each<Transform>()) {
			ent->with<Transform, Mesh, Material>([&](ECS::ComponentHandle<Transform> tr, ECS::ComponentHandle<Mesh> mesh, ECS::ComponentHandle<Material> mat) {

				if (mat->shader == nullptr) mat->shader = defaultShader;
				if (mat->texture == nullptr) {
					unsigned char white[] = {255,255,255};
					mat->texture = new Texture(white, 1, 1, 3, GL_TEXTURE_2D);
				}
				
				mat->shader->Activate();
				mat->shader->UploadUniform4f("color", mat->color);
				if (mat->texture != nullptr) {
					mat->shader->UploadUniform1i("tex0", 0);
					mat->texture->Bind();
				}
				
				// Generate Model Matrix from Transform //
				glm::mat4 model = glm::mat4(1.0f);
				glm::vec3 finalPos = tr->position;
				
				model = glm::translate(model, finalPos);

				model = glm::rotate(model, glm::radians(tr->rotation.x), glm::vec3(1,0,0));
				model = glm::rotate(model, glm::radians(tr->rotation.y), glm::vec3(0,1,0));
				model = glm::rotate(model, glm::radians(tr->rotation.z), glm::vec3(0,0,1));
				model = glm::scale(model, tr->scale);
				
				if (mat->texture->width != mat->texture->height) {
					double w = (double)(mat->texture->width);
					double h = (double)(mat->texture->height);
					double d = w > h ? w : h;
					model = glm::scale(model, glm::vec3(w/d, h/d, 1.0) );
				}

				if (mat->shader != nullptr) {
					mat->shader->UploadUniformMatrix4fv("_MVP", camera.projection * camera.view * model);
				}

				// Draw Mesh //
				glActiveTexture(GL_TEXTURE0);

				glBindVertexArray(mesh->VAO);
				glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			});
		}
		OnDrawGUI.Invoke();
		

		glfwSwapBuffers(currentWindow->Get());
		glfwPollEvents();
	};

	int Engine::run (Window* window) {
		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);
		
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

		world->destroyWorld();

		OnQuit.Invoke();

		glfwDestroyWindow(window->Get());
		glfwTerminate();
		return 0;
	}
}