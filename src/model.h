#pragma once

#include "../include/tiny_obj_loader.h"
#include "../include/tiny_gltf_loader.h"

#include "internal/res_teapot.h"

#include <glm/gtx/hash.hpp>
#include <unordered_map>

#include "mesh.h"
#include "resources.h"

namespace Blackbox {

	// WIP //
	inline void LoadGLTF () {
		tinygltf::Scene scene; 
		tinygltf::TinyGLTFLoader loader;
		std::string err;
		
		bool ret = loader.LoadASCIIFromFile(&scene, &err, "res/BoxTextured.gltf");
		auto m = scene.meshes.at(0).name.c_str();
		
		
		// Entity* ent = CreateQuad(m);
		// ent->mesh = Mesh(scene.meshes.at(0));
	}

	inline Mesh LoadObj (std::istringstream src) {

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		if (src) {
			tinyobj::LoadObj(&attrib, &shapes, &materials, &err, &src);
		}	

		if (!warn.empty()) LogInternal(warn);
		if (!err.empty()) LogError(err);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		std::unordered_map<glm::vec3, uint32_t> uniqueVertices;

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vert = Vertex();

				glm::vec3 position {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				if (uniqueVertices.count(position) == 0) {
					uniqueVertices[position] = static_cast<uint32_t>(vertices.size());
					vert.Position = position;
				}

				if (index.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2*size_t(index.texcoord_index)+0];
					tinyobj::real_t ty = attrib.texcoords[2*size_t(index.texcoord_index)+1];

					vert.TexCoords = glm::vec2(tx, ty);
				}
				else {
					srand( index.vertex_index );
					float val = (float) rand()/RAND_MAX;
					vert.TexCoords = glm::vec2(val, val);
				}

				
				vertices.push_back(vert);
				indices.push_back(uniqueVertices[position]);
				
			}
		}
		return Mesh(vertices, indices);
	}
	
	inline Mesh LoadObj (const char* filePath) {

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		if (filePath) {
			std::string inputfile = resFolder + filePath;
			tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());
		}

		if (!warn.empty()) LogInternal(warn);
		if (!err.empty()) LogError(err);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		std::unordered_map<glm::vec3, uint32_t> uniqueVertices;

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vert = Vertex();

				glm::vec3 position {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				if (uniqueVertices.count(position) == 0) {
					uniqueVertices[position] = static_cast<uint32_t>(vertices.size());
					vert.Position = position;
				}

				if (index.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2*size_t(index.texcoord_index)+0];
					tinyobj::real_t ty = attrib.texcoords[2*size_t(index.texcoord_index)+1];

					vert.TexCoords = glm::vec2(tx, ty);
				}
				else {
					srand( index.vertex_index );
					float val = (float) rand()/RAND_MAX;
					vert.TexCoords = glm::vec2(val, val);
				}

				
				vertices.push_back(vert);
				indices.push_back(uniqueVertices[position]);
				
			}
		}
		return Mesh(vertices, indices);
	}
}