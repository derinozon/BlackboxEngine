#pragma once

#include <typeinfo>
#include <vector>

// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

#include "mesh.h"
#include "entity.h"
#ifndef __EMSCRIPTEN__
// #include "model.h"
#endif

#ifndef WIN
#include <filesystem>
namespace fs = std::filesystem;
#endif

namespace ENG {
	#ifndef WIN
	static fs::path resFolder = fs::current_path() / fs::path("res");
	#else
	static std::string resFolder = "./res/";
	#endif
	
	namespace Resources {
		
		// FS Version //
		/*
		
		*/
		#ifdef WIN
		inline std::string Load (const char* path) {
			std::string out;
			std::ifstream infile(resFolder+path);
			infile >> out;
			infile.close();
			return out;
		}
	
		template <typename T>
		inline T* Load (const char* path) {
			return new T( (resFolder+path).c_str() );
		}
		#else
		inline void SetPath (const char* path) {
			resFolder = fs::current_path() / fs::path(path);
		}

		inline std::string Load (const char* path) {
			std::string out;
			std::ifstream infile((resFolder/fs::path(path)));
			infile >> out;
			infile.close();
			return out;
		}
	
		template <typename T>
		inline T* Load (const char* path) {
			return new T( (resFolder/fs::path(path)).c_str() );
		}
		#endif
		// void GenerateModel (aiNode *node, const aiScene *scene) {

		// 	// std::cout << node->mName.C_Str() << std::endl;
		// 	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		// 		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];	
		// 		Mesh m = processMesh(mesh, scene);

		// 		Texture* metalTex = Load<Texture>("HourglassUV.png");
		// 		entt::entity entity = registry.create();
		// 		auto t = registry.emplace<Transform>(entity);

		// 		aiQuaterniont<float>  	rotation(0,0,0,0);
		// 		aiVector3t<float>  	position(2,0,0);
				
		// 		node->mTransformation.DecomposeNoScaling(rotation, position);
		// 		glm::mat4 matrix = mat4_cast(node->mTransformation);

		// 		t.position = vec3_cast(position);
		// 		std::cout << t.position.x << std::endl;
		// 		std::cout << position.x << std::endl;
		// 		registry.emplace<Mesh>(entity, m.vertices, m.indices);
		// 		registry.emplace<Material>(entity, defaultShader, metalTex);
		// 	}
			
		// 	for(unsigned int i = 0; i < node->mNumChildren; i++) {
		// 		GenerateModel(node->mChildren[i], scene);
		// 	}
			
		// }

		// void MakeModel (const char* path) {
		// 	Assimp::Importer importer;
		// 	const char* modelPath = (resFolder/fs::path(path)).c_str();
		// 	const aiScene *scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

		// 	GenerateModel(scene->mRootNode, scene);
		// }

		#ifndef __EMSCRIPTEN__
		// Model LoadModel (const char* path) {
		// 	// Too much copying pass by referance !!! //
		// 	Assimp::Importer importer;
		// 	const char* modelPath = (resFolder/fs::path(path)).c_str();
		// 	const aiScene *scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs); 
		// 	
		// 	return processNode(scene->mRootNode, scene);
		// }

		// Entity* LoadModelAsEntity (const char* path) {
		// 	// Too much copying pass by referance !!! //
		// 	Assimp::Importer importer;
		// 	const char* modelPath = (resFolder/fs::path(path)).c_str();
		// 	const aiScene *scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs); 
			
		// 	// return processNode(scene->mRootNode, scene);
		// 	return new Entity();
		// }
		#else
		inline std::vector<Mesh> LoadModel (const char* path);
		#endif

		
	}
}