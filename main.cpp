#include "engine.h"

using namespace ENG;
using namespace glm;

void Serialize (JSON_Object* json, std::string str, glm::vec3 vec) {
	json_object_dotset_number(json, (str+".x").c_str(), vec.x);
	json_object_dotset_number(json, (str+".y").c_str(), vec.y);
	json_object_dotset_number(json, (str+".z").c_str(), vec.z);
}

std::string Serialize (Entity* ent) {
	JSON_Value *root_value = json_value_init_object();
	JSON_Object *root_object = json_value_get_object(root_value);
	char *serialized_string = NULL;
	json_object_set_string(root_object, "name", ent->name.c_str());

	Serialize(root_object, "transform.position", ent->transform.position);
	Serialize(root_object, "transform.rotation", ent->transform.rotation);
	Serialize(root_object, "transform.scale", ent->transform.scale);

	//json_object_dotset_value(root_object, "contact.emails", json_parse_string("[\"email@example.com\",\"email2@example.com\"]"));
	serialized_string = json_serialize_to_string_pretty(root_value);
	json_value_free(root_value);
	puts(serialized_string);

	return serialized_string;
}

void LoadObj (std::string str) {
	JSON_Value* root_value = json_parse_string(str.c_str());
    
    auto commits = json_value_get_object(root_value);
    auto s = json_object_get_string(commits, "name");
	Log("ALL : ", str);
	Log("STRING : ", s);
    //json_object_dotget_number(commit, "commit.author.date")
    
    
    /* cleanup code */
    json_value_free(root_value);
}

void crate () {
	Texture* crateTex = Resources::LoadTexture("crate.png");
	Entity* ent = CreateQuad("Crate");
	
	ent->transform = {vec3(0, 0, -1.5), vec3(0,0,45), vec3(3,3,3)};
	ent->material = Material(defaultShader, crateTex);

	LoadObj( Serialize(ent) );
}

int main() {
	/*
	#ifdef WIN
	resFolder = "C:\\Users\\admin\\Documents\\Github\\BlackboxEngine\\res\\";
	#endif
	*/
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