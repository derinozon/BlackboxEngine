#include "serialization.h"

#include "transform.h"
#include "mesh.h"

/*
namespace glm {
    void to_json(nlohmann::json& j, const vec2& P) {
        j = { { "x", P.x }, { "y", P.y } };
    };

    void from_json(const nlohmann::json& j, vec2& P) {
        P.x = j.at("x").get<double>();
        P.y = j.at("y").get<double>();
    }

	void to_json(nlohmann::json& j, const vec3& P) {
        j = { { "x", P.x }, { "y", P.y }, { "z", P.z } };
    };

    void from_json(const nlohmann::json& j, vec3& P) {
        P.x = j.at("x").get<double>();
        P.y = j.at("y").get<double>();
		P.z = j.at("z").get<double>();
    }
}

namespace ENG {
	// void to_json(nlohmann::json& j, const Mesh& P) {
    //     j = { "resourceHandle", P.resourceHandle };
    // };

    // void from_json(const nlohmann::json& j, Mesh& P) {
    //     P.resourceHandle = j.at("resourceHandle").get<std::string>();
    // }
}

namespace ENG {
	void LoadScene (const char* path) {
		std::string json_output;
		std::ifstream infile(path);
		infile >> json_output;
		infile.close();
	}

	void SaveScene (const char* path) {
		nlohmann::json j = *ent;
		
		std::ofstream outfile(path);
		// Loop Through the scene //
		outfile << j;
		outfile.close();
	}
}
*/