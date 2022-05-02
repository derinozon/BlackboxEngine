#include "engine.h"
#include "tiny_obj_loader.h"

using namespace ENG;
using namespace glm;

void crate () {
	Entity* ent = CreateQuad("Crate");
	
	ent->transform = {vec3(0, 0, -1.5), vec3(0,0,45), vec3(3,3,3)};
	ent->material = Material("crate.png");
}


void LoadObj () {
	std::string inputfile = resFolder + "teapot.obj";
	Log(inputfile);
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

	if (!warn.empty()) {
	std::cout << warn << std::endl;
	}

	if (!err.empty()) {
	std::cerr << err << std::endl;
	}

	if (!ret) {
	exit(1);
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
			
			//indices.push_back(shapes[s].mesh.indices[f*3].vertex_index);
			//for(unsigned int j = 0; j < shapes[s].mesh.indices.size(); j++)
				//indices.push_back(shapes[s].mesh.indices[j].vertex_index); 

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
				tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
				tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
				
				Vertex vertex;
				vertex.Position = glm::vec3(vx, vy, vz);
				
				// Check if `normal_index` is zero or positive. negative = no normal data
				if (idx.normal_index >= 0) {
					tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
					tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
					tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];

					vertex.Normal = glm::vec3(nx, ny, nz);
				}

				// Check if `texcoord_index` is zero or positive. negative = no texcoord data
				if (idx.texcoord_index >= 0) {
					tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
					tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];

					vertex.TexCoords = glm::vec2(tx, ty);
				}

				vertices.push_back(vertex);

				// Optional: vertex colors
				// tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
				// tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
				// tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
			}
			indices.push_back(f*2);
			index_offset += fv;
			

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	auto teapot = CreateQuad("Teapot");
	teapot->mesh = Mesh(vertices, indices);
	//teapot->material = Material("crate.png");
}

int main() {
	Window* window = ENG::init("Blackbox Engine");
	
	// crate();
	LoadObj();

	

	OnDrawGUI = []() {
		int val = 1;

		ImGui::Begin("Debug");
		Editor::IntField("Index Mult.", &val);
		ImGui::End();
	};
	
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

		entityList[0]->transform.rotation.y += speed;
	};
	ENG::run(window);
	
	return 0;
}