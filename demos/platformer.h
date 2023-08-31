// #include "../src/editor.h"
#include "../blackbox.h"

using namespace Blackbox;
using namespace glm;

class PhysicsBody {
	public:
	float gravityScale = 1;
	vec3 velocity = vec3(0);
	PhysicsBody* collidingBody = nullptr;
};

typedef struct {
	float x, y, w, h;
} Rect;

bool AABB (Rect a, Rect b) {
	return 
		a.x < b.x + b.w &&
		a.x + a.w > b.x &&
		a.y < b.y + b.h &&
		a.y + a.h > b.y;
}

typedef struct {
} Character;

class CharacterSystem : public ECS::EntitySystem {
public:
	float movementSpeed = 5;
	Engine* engine;

	CharacterSystem(){}
	CharacterSystem(Engine* eng){
		engine = eng;
	}
    
    virtual ~CharacterSystem() {}
    
    virtual void tick(ECS::World* world, float deltaTime) override {
		world->each<Character, Transform, PhysicsBody>([&](ECS::Entity* ent, ECS::ComponentHandle<Character> character, ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<PhysicsBody> rb) {
			transform->position += vec3(
				engine->Input.GetAxisHorizontal() * deltaTime * movementSpeed,
				engine->Input.GetAxisVertical() * deltaTime * movementSpeed,
				0
			);
        });
    }
};


class PhysicsSystem : public ECS::EntitySystem {
public:

	PhysicsSystem() {}

	virtual ~PhysicsSystem() {}

	virtual void tick(ECS::World* world, float deltaTime) override {
		world->each<Transform, PhysicsBody>([&](ECS::Entity* ent, ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<PhysicsBody> rb) {
			Rect a;
			a.x = transform->position.x;
			a.y = transform->position.y;
			a.w = transform->scale.x;
			a.h = transform->scale.y;

			world->each<Transform, PhysicsBody>([&](ECS::Entity* otherEnt, ECS::ComponentHandle<Transform> otherTransform, ECS::ComponentHandle<PhysicsBody> otherRb) {
				if (ent != otherEnt) {
					Rect b;
					b.x = otherTransform->position.x;
					b.y = otherTransform->position.y;
					b.w = otherTransform->scale.x;
					b.h = otherTransform->scale.y;

					if (AABB(a, b)) {
						rb->collidingBody = &(otherRb.get());
						otherRb->collidingBody = &rb.get();
						ent->get<Material>().get().color = vec4(0.7, 0.3, 0.3, 1);
					}
					else {
						ent->get<Material>().get().color = vec4(1, 1, 1, 1);
					}
				}
			});
		});
	}
};

void Platformer(Engine* engine) {
	float col = 20.0 / 255.0;
	engine->clearColor = vec4(col, col, col, 1.0f);
	engine->camera->perspective = false;
	engine->world->registerSystem(new CharacterSystem(engine));
	engine->world->registerSystem(new PhysicsSystem());

	ECS::Entity* ground = CreateQuad(engine->world);
	ground->assign<PhysicsBody>();
	auto transform = ground->get<Transform>();
	transform->position += vec3(0, -3, 0);
	transform->scale = vec3(9.0, 0.7, 1.0);

	ECS::Entity* character = CreateQuad(engine->world);
	character->assign<PhysicsBody>();
	character->assign<Character>();
	character->get<Transform>()->scale = vec3(1);

	ECS::Entity* box = CreateQuad(engine->world);
	box->assign<PhysicsBody>();
	box->get<Transform>()->position += vec3(2, 0, 0);
	box->get<Transform>()->scale = vec3(1);
}