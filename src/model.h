#pragma once

#include "../include/tiny_obj_loader.h"
#include "internal/res_teapot.h"

#include <glm/gtx/hash.hpp>
#include <unordered_map>

#include "mesh.h"
#include "resources.h"

namespace Blackbox {
	// Give nullptr to render default model
	inline Mesh LoadObj (const char* filePath) {

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		if (filePath) {
			std::string inputfile = resFolder + "teapot.obj";
			tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());
		}
		else {
			std::istringstream src = std::istringstream(TEAPOT_MODEL);
			tinyobj::LoadObj(&attrib, &shapes, &materials, &err, &src);
		}
		

		if (!warn.empty()) {
		std::cout << warn << std::endl;
		}

		if (!err.empty()) {
		std::cerr << err << std::endl;
		}

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