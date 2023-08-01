// #include "../src/editor.h"
#include "../blackbox.h"

using namespace Blackbox;
using namespace glm;

struct Body {
	float mass;
	glm::vec3 velocity;

	Body(){}

	Body(float bodyMass, glm::vec3 bodyVelocity) {
		mass = bodyMass;
		velocity = bodyVelocity;
	}
};

class ParticleSystem : public ECS::EntitySystem {
public:
	ParticleSystem(){}
    
    virtual ~ParticleSystem() {}
    
    virtual void tick(ECS::World* world, float deltaTime) override {
		float G = 1;
		float dt = deltaTime;
		float damping = 0.1 * 4.0;
		float centeringForce = 0.01;

		for (int i = 0; i < world->getCount(); i++) {
			glm::vec3 acceleration(0.0f);
			auto particle = world->getByIndex(i);
			auto particleTransform = particle->get<Transform>();
			auto particleBody = particle->get<Body>();

			for (int a = 0; a < world->getCount(); a++) {
				auto other = world->getByIndex(a);
				auto otherTransform = other->get<Transform>();
				auto otherBody = other->get<Body>();

				if (particle != other) {
					// Calculate the distance and direction between particles
					glm::vec3 direction = otherTransform->position - particleTransform->position;
					float distance = glm::length(direction);
					glm::vec3 forceDirection = glm::normalize(direction);
					// Calculate the gravitational force
					float force = G * (particleBody->mass * otherBody->mass) / (distance * distance);
					glm::vec3 gravitationalForce = force * forceDirection;

					// Update the acceleration of the particle
					acceleration += gravitationalForce / particleBody->mass;
				}
			}

			// Apply damping force to the velocity of the particle
			glm::vec3 dampingForce = -damping * particleBody->velocity;
			acceleration += dampingForce;

			// Apply centering force towards the center of the world
			glm::vec3 directionToCenter = -particleTransform->position;
			glm::vec3 centeringForce = directionToCenter;
			acceleration += centeringForce;
			// Update the velocity and position of the particle using the Verlet integration method
			particleBody->velocity += acceleration * dt;
			particle->get<Transform>()->position += particleBody->velocity * dt + 0.5f * acceleration * dt * dt;
		}
    }
};

void ParticleECS (Engine* engine) {
	const int particleSize = 50;
	std::srand(Time.time);

	engine->world->registerSystem(new ParticleSystem());

	// Spawn Particles
	for (int i = 0; i < particleSize; i++) {
		float size = RandomRange(1, 5);
		auto obj = LoadObj(std::istringstream(SPHERE_MODEL)); 

		ECS::Entity* particle = engine->world->create();
		particle->assign<Transform>(RandomBox(5) ,glm::vec3(0) ,glm::vec3(size * 0.01));
		particle->assign<Mesh>(obj.vertices, obj.indices);
		particle->assign<Material>()->color = RandomColor();
		particle->assign<Body>(size, glm::vec3(0.0f));
	}

	float col = 20.0/255.0;
	engine->clearColor = vec4(col, col, col, 1.0);
}