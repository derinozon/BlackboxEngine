#include "blackbox.h"

namespace Blackbox {

	#ifdef __EMSCRIPTEN__
	EMSCRIPTEN_KEEPALIVE int framebuffer_size_callback(int eventType, const EmscriptenUiEvent* uiEvent, void* userData) {
		int width = uiEvent->windowInnerWidth;
		int height = uiEvent->windowInnerHeight;

		emscripten_set_canvas_element_size("#canvas", width, height);
		Camera* camera = static_cast<Camera*>(userData);

		camera->width = width;
		camera->height = height;
		glViewport(0, 0, width, height);
		LogInternal("Window resize: ", width, " ", height);
		return 0;
	}

	void getViewportSize(int& width, int& height) {
		width = EM_ASM_INT({
			return window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
		});
		height = EM_ASM_INT({
			return window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight;
		});
	}

	static void emscriptenLoop(void* arg) {
		Engine* engine = static_cast<Engine*>(arg);
        engine->loop(arg);
    }
	#endif

	Window* Engine::init (Configuration configuration) {
		return init(
			configuration.title,
			configuration.width,
			configuration.height,
			configuration.fullscreen,
			configuration.vsync,
			configuration.resizable
		);
	}

	Window* Engine::init (const char* title, int width, int height, bool fullscreen, bool vsync, bool resizable) {
		camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 5.0f));
		clearColor = glm::vec4(0.07f, 0.13f, 0.17f, 1.0f);
		
		// Initialize GLFW
		glfwSetErrorCallback([](int error, const char *msg){
			LogError(error, ' ', msg);
		});
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, resizable);

		// glfwWindowHint(GLFW_DECORATED , 0);
		#ifndef __EMSCRIPTEN__
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER , 1);
		#endif

		glfwWindowHint(GLFW_SAMPLES  , 8);
		glfwWindowHint(GLFW_SRGB_CAPABLE, 1);
		
		Window* window = new Window(title, width, height, fullscreen);
		
		if (window->Get() == NULL) {
			LogError("Failed to create GLFW window");
			glfwTerminate();
		}
		
		glfwSetWindowUserPointer(window->Get(), this);
		glfwMakeContextCurrent(window->Get());
		LogInternal("GLContext success");
		
		//Load GLAD so it configures OpenGL
		#ifndef __EMSCRIPTEN__
			glfwSwapInterval(vsync);
			gladLoadGL();
		#endif


		#ifdef __EMSCRIPTEN__
			emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, camera, 1, &framebuffer_size_callback);
			int viewportWidth, viewportHeight;
			getViewportSize(viewportWidth, viewportHeight);

			emscripten_set_canvas_element_size("#canvas", viewportWidth, viewportHeight);
			camera->width = viewportWidth;
			camera->height = viewportHeight;
			glViewport(0, 0, viewportWidth, viewportHeight);
		#else
			auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
				Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
				engine->camera->width = width;
				engine->camera->height = height;
				glViewport(0, 0, width, height);
			};
			glfwSetFramebufferSizeCallback(window->Get(), framebuffer_size_callback);
			framebuffer_size_callback(window->Get(), width, height);
		#endif

		LogInternal("Viewport success");

		auto drop_callback = [] (GLFWwindow* window, int count, const char** paths) {
			const char* name = paths[0];
			Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
			auto ent = CreateQuad(engine->world);
			ent->get<Material>()->texture = new Texture(paths[0]);
		};

		glfwSetDropCallback(window->Get(), drop_callback);

		camera->perspective = true;

		currentWindow = window;
		world = ECS::World::createWorld();
		return window;
	}

	void Engine::loop (void* arg){
		Engine* engine = static_cast<Engine*>(arg);
		engine->Input.SetWindow(engine->currentWindow->Get());

		// Calculate deltatime //
		Time.time = glfwGetTime();
		Time.deltaTime = Time.time - Time.lastFrameTime;
		Time.lastFrameTime = Time.time;
		
		// Enable blending //
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glClearColor(engine->clearColor.x, engine->clearColor.y, engine->clearColor.z, engine->clearColor.w);
		// Clean the back buffer and depth buffer //
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine->camera->UpdateMatrix();
		engine->OnUpdate.Invoke();
		engine->world->tick(Time.deltaTime);

		Shader* defaultShader = new Shader(
			DEFAULT_UNLIT_VERT,
			DEFAULT_UNLIT_FRAG
		);

		// Draw Meshes //
		for (ECS::Entity* ent : engine->world->each<Transform>()) {
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
					mat->shader->UploadUniformMatrix4fv("_MVP", engine->camera->projection * engine->camera->view * model);
				}

				// Draw Mesh //
				glActiveTexture(GL_TEXTURE0);

				glBindVertexArray(mesh->VAO);
				glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			});
		}
		engine->OnDrawGUI.Invoke();
		
		glfwSwapBuffers(engine->currentWindow->Get());
		glfwPollEvents();
	};

	int Engine::run (Window* window) {
		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);
		
		#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg(emscriptenLoop, this, 0, 1);
		#else
		while (!glfwWindowShouldClose(window->Get())) {
			loop(this);
		}
		#endif

		delete camera;
		world->destroyWorld();
		delete window;
		OnQuit.Invoke();

		glfwDestroyWindow(window->Get());
		glfwTerminate();
		return 0;
	}
}