// #include "../src/editor.h"
#include "../blackbox.h"

using namespace Blackbox;
using namespace glm;

typedef struct {
	float gravity = -9;
} PhysicsBody;

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
		world->each<Transform, PhysicsBody>([&](ECS::Entity* ent, ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<PhysicsBody> rb) {
			transform->position += vec3(engine->Input.GetAxisHorizontal() * deltaTime * movementSpeed, 0, 0);
        });
    }
};

void Platformer (Engine* engine) {
	engine->world->registerSystem(new CharacterSystem(engine));

	ECS::Entity* ground = CreateQuad(engine->world);
	auto transform = ground->get<Transform>();
	transform->position += vec3(0, -3, 0);
	transform->scale = vec3(9.0, 0.7, 1.0);

	ECS::Entity* character = CreateQuad(engine->world);
	character->assign<PhysicsBody>();
	character->get<Transform>()->scale = vec3(0.5);
	
	float col = 20.0/255.0;
	engine->clearColor = vec4(col, col, col, 1.0);
}