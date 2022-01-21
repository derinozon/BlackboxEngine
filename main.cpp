#include "engine.h"

using namespace ENG;
using namespace glm;

void Serialize (JSON_Object* json, std::string str, glm::vec3 vec) {
	json_object_dotset_number(json, (str+".x").c_str(), vec.x);
	json_object_dotset_number(json, (str+".y").c_str(), vec.y);
	json_object_dotset_number(json, (str+".z").c_str(), vec.z);
}

glm::vec3 DeSerialize (JSON_Object* json, std::string str) {
	return glm::vec3(
		json_object_dotget_number(json, (str+".x").c_str()),
		json_object_dotget_number(json, (str+".y").c_str()),
		json_object_dotget_number(json, (str+".z").c_str())
	);
}

std::string Serialize (Entity* ent) {
	JSON_Value *root_value = json_value_init_object();
	JSON_Object *root_object = json_value_get_object(root_value);
	char *serialized_string = NULL;
	json_object_set_string(root_object, "name", ent->name.c_str());

	Serialize(root_object, "transform.position", ent->transform.position);
	Serialize(root_object, "transform.rotation", ent->transform.rotation);
	Serialize(root_object, "transform.scale", ent->transform.scale);

	json_object_set_string(root_object, "mesh.resHandle", ent->mesh.resourceHandle.c_str());
	json_object_set_string(root_object, "material.textureHandle", ent->material.texturePath.c_str());

	//json_object_dotset_value(root_object, "contact.emails", json_parse_string("[\"email@example.com\",\"email2@example.com\"]"));
	serialized_string = json_serialize_to_string_pretty(root_value);
	json_value_free(root_value);

	return serialized_string;
}

Entity* Deserialize (std::string str) {
	JSON_Value* root_value = json_parse_string(str.c_str());
    
    JSON_Object* obj = json_value_get_object(root_value);
    auto s = json_object_get_string(obj, "name");
	Log("ALL : ", str);
	Log("STRING : ", s);
	Entity* ent = CreateQuad(s);
	ent->transform.position = DeSerialize(obj, "transform.position");
	ent->transform.rotation = DeSerialize(obj, "transform.rotation");
	ent->transform.scale = DeSerialize(obj, "transform.scale");

	ent->mesh.resourceHandle = json_object_get_string(obj, "mesh.resHandle");
	ent->material.texturePath = json_object_get_string(obj, "material.textureHandle");
	
	if (!ent->mesh.resourceHandle.empty()) {
		// Load Mesh //
	}
    if (!ent->material.texturePath.empty()||ent->material.texturePath!="") {
		ent->material = Material(ent->material.texturePath.c_str());
	}
    
    
    /* cleanup code */
    json_value_free(root_value);
	return ent;
}

void crate () {
	Entity* ent = CreateQuad("Crate");
	
	ent->transform = {vec3(0, 0, -1.5), vec3(0,0,45), vec3(3,3,3)};
	ent->material = Material("crate.png");

	Deserialize( Serialize(ent) );
}

int main() {
	Log(resFolder);
	Window* window = ENG::init("Blackbox Engine");
	
	crate();
	
	GameLoop = []() {
		float speed = 10.0f * Time.deltaTime;
		
		camera.Position += speed * glm::vec3(1,0,0) * Input.GetAxisHorizontal();
		camera.Position += speed * glm::vec3(0,0,-1) * Input.GetAxisVertical();
		
		if (Input.GetKey(GLFW_KEY_SPACE)) {
			camera.Position += speed * glm::vec3(0,1,0);
		}
		if (Input.GetKey(GLFW_KEY_LEFT_CONTROL)) {
			camera.Position += speed * glm::vec3(0,-1,0);
		}
	};
	ENG::run(window);
	
	return 0;
}

// SSL aydinozon
// Revolando -> aydinozon
// new revolando -> persona anima