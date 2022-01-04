#pragma once

// #include <nlohmann/json.hpp>
#include <glm/glm.hpp>
/*
namespace glm {
    void to_json(nlohmann::json& j, const vec2& P);
    void from_json(const nlohmann::json& j, vec2& P);

	void to_json(nlohmann::json& j, const vec3& P);
    void from_json(const nlohmann::json& j, vec3& P);
}

namespace ENG {
	void LoadScene (const char* path);
	void SaveScene (const char* path);
}
*/
// namespace std {
//     void to_json(nlohmann::json& j, const vector& P);
//     void from_json(const nlohmann::json& j, vector& P);
// }

// namespace ENG {
// 	void to_json(nlohmann::json& j, const Vertex& P) {
//         j = { { "Position", P.Position }, { "Normal", P.Normal }, { "TexCoords", P.TexCoords } };
//     };

//     void from_json(const nlohmann::json& j, Vertex& P) {
//         P.Position = j.at("Position").get<glm::vec3>();
//         P.Normal = j.at("Normal").get<glm::vec3>();
// 		P.TexCoords = j.at("TexCoords").get<glm::vec2>();
//     }
// }