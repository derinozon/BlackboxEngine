#include "entity.h"

namespace ENG {

	Entity::Entity(std::string entityName) {
		Log("Creating Entity");
		name = entityName;
		
		for (Entity* ent : entityList) {
			if (ent->name == entityName) {
				
			}
		}
		
		entityList.push_back(this);
	}

	Entity::Entity() {
		Entity("Entity");
	}

	Entity::~Entity() {
		Log("Destroying Entity");
	}

}