// #include "../src/editor.h"
#include "../blackbox.h"

using namespace Blackbox;
using namespace glm;

std::vector<float> mass;
std::vector<glm::vec3> velocity;

ECS::World* world;
Engine* lol;

void ParticleECS (Engine* engine) {
	lol = engine;
	const int particleSize = 50;
	std::srand(Time.time);

	world = ECS::World::createWorld();

	

	lol->OnUpdate += []{
		// world->tick(Time.deltaTime);

		for (ECS::Entity* ent : world->each<Transform>()) {
			ent->with<Transform, Mesh, Material>([&](ECS::ComponentHandle<Transform> tr, ECS::ComponentHandle<Mesh> mesh, ECS::ComponentHandle<Material> mat) {

				if (mat->shader == nullptr) mat->shader = lol->defaultShader;
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
					mat->shader->UploadUniformMatrix4fv("_MVP", lol->camera.projection * lol->camera.view * model);
				}

				// Draw Mesh //
				glActiveTexture(GL_TEXTURE0);

				glBindVertexArray(mesh->VAO);
				glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			});
		}
	};
	
	auto spawnParticle = []() {
		float size = RandomRange(1, 5);
		auto obj = LoadObj(std::istringstream(SPHERE_MODEL)); 

		ECS::Entity* particle = world->create();
		particle->assign<Transform>(RandomBox(5),glm::vec3(0),glm::vec3(size * 0.01));
		particle->assign<Mesh>(obj.vertices, obj.indices);
		particle->assign<Material>()->color = RandomColor();

		mass.push_back(size);
        velocity.push_back(glm::vec3(0.0f));
	};

	for (int i = 0; i < particleSize; i++) {
		spawnParticle();
	}

	float col = 20.0/255.0;
	engine->clearColor = vec4(col, col, col, 1.0);

	engine->OnUpdate += []() {
        float G = 1;
        float dt = Time.deltaTime;
		float damping = 0.1 * 4.0;
        float centeringForce = 0.01;

        for (int i = 0; i < world->getCount(); i++) {
            glm::vec3 acceleration(0.0f);
			auto particle = world->getByIndex(i);

            for (int a = 0; a < world->getCount(); a++) {
				auto other = world->getByIndex(a);

                if (particle != other) {
                    // Calculate the distance and direction between particles
                    glm::vec3 direction = other->get<Transform>()->position - particle->get<Transform>()->position;
                    float distance = glm::length(direction);
                    glm::vec3 forceDirection = glm::normalize(direction);
                    // Calculate the gravitational force
                    float force = G * (mass[i] * mass[a]) / (distance * distance);
                    glm::vec3 gravitationalForce = force * forceDirection;

                    // Update the acceleration of the particle
                    acceleration += gravitationalForce / mass[i];
                }
            }

            // Apply damping force to the velocity of the particle
            glm::vec3 dampingForce = -damping * velocity[i];
            acceleration += dampingForce;

            // Apply centering force towards the center of the world
            glm::vec3 directionToCenter = -particle->get<Transform>()->position;
            glm::vec3 centeringForce = directionToCenter;
            acceleration += centeringForce;

            // Update the velocity and position of the particle using the Verlet integration method
            velocity[i] += acceleration * dt;
            particle->get<Transform>()->position += velocity[i] * dt + 0.5f * acceleration * dt * dt;
        }
    };
}

void Particle (Engine* engine) {
	const int particleSize = 50;
	std::srand(Time.time);
	
	auto spawnParticle = []() {
		float size = RandomRange(1, 5);

		auto particle = CreateQuad("Particle");
		particle->transform.position = RandomBox(5);
		particle->transform.scale *= size * 0.01;
		particle->mesh = LoadObj(std::istringstream(SPHERE_MODEL));
		particle->material.color = RandomColor();

		mass.push_back(size);
        velocity.push_back(glm::vec3(0.0f));
	};

	for (int i = 0; i < particleSize; i++) {
		spawnParticle();
	}
	
	float col = 20.0/255.0;
	engine->clearColor = vec4(col, col, col, 1.0);

	engine->OnUpdate += []() {
        float G = 1;
        float dt = Time.deltaTime;
		float damping = 0.1 * 4.0;
        float centeringForce = 0.01;

        for (int i = 0; i < entityList.size(); i++) {
            glm::vec3 acceleration(0.0f);
			auto particle = entityList[i];

            for (int a = 0; a < entityList.size(); a++) {
				auto other = entityList[a];

                if (particle != other) {
                    // Calculate the distance and direction between particles
                    glm::vec3 direction = other->transform.position - particle->transform.position;
                    float distance = glm::length(direction);
                    glm::vec3 forceDirection = glm::normalize(direction);
                    // Calculate the gravitational force
                    float force = G * (mass[i] * mass[a]) / (distance * distance);
                    glm::vec3 gravitationalForce = force * forceDirection;

                    // Update the acceleration of the particle
                    acceleration += gravitationalForce / mass[i];
                }
            }

            // Apply damping force to the velocity of the particle
            glm::vec3 dampingForce = -damping * velocity[i];
            acceleration += dampingForce;

            // Apply centering force towards the center of the world
            glm::vec3 directionToCenter = -particle->transform.position;
            glm::vec3 centeringForce = directionToCenter;
            acceleration += centeringForce;

            // Update the velocity and position of the particle using the Verlet integration method
            velocity[i] += acceleration * dt;
            particle->transform.position += velocity[i] * dt + 0.5f * acceleration * dt * dt;
        }
    };
}