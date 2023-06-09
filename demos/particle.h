// #include "../src/editor.h"
#include "../blackbox.h"

using namespace Blackbox;
using namespace glm;

std::vector<float> mass;
std::vector<glm::vec3> velocity;

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