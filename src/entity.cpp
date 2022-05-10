#include "entity.h"

namespace Blackbox {

	Entity::Entity(std::string entityName) {
		Log("Creating Entity");
		name = entityName;
		entityList.push_back(this);
	}

	Entity::Entity() {
		Entity("Entity");
	}

	Entity::~Entity() {
		Log("Destroying Entity");
		for (int i = 0; i < entityList.size(); i++){
			if (entityList[i] == this){
				entityList.erase(entityList.begin()+i);
				break;
			}
		}
	}

}