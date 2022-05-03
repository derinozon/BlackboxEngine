#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

// Assimp to glm conversions //
static inline glm::vec3 vec3_cast(const aiVector3D &v) { return glm::vec3(v.x, v.y, v.z); }
static inline glm::vec2 vec2_cast(const aiVector3D &v) { return glm::vec2(v.x, v.y); }
static inline glm::quat quat_cast(const aiQuaternion &q) { return glm::quat(q.w, q.x, q.y, q.z); }
static inline glm::mat4 mat4_cast(const aiMatrix4x4 &m) { return glm::transpose(glm::make_mat4(&m.a1)); }
static inline glm::mat4 mat4_cast(const aiMatrix3x3 &m) { return glm::transpose(glm::make_mat3(&m.a1)); }

namespace ENG {

	inline Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
			// data to fill
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			

			// walk through each of the mesh's vertices
			for(unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
				// positions
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.Position = vector;
				// normals
				if (mesh->HasNormals())
				{
					vector.x = mesh->mNormals[i].x;
					vector.y = mesh->mNormals[i].y;
					vector.z = mesh->mNormals[i].z;
					vertex.Normal = vector;
				}
				// texture coordinates
				if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					glm::vec2 vec;
					// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
					vec.x = mesh->mTextureCoords[0][i].x; 
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.TexCoords = vec;
					/*
					// tangent
					vector.x = mesh->mTangents[i].x;
					vector.y = mesh->mTangents[i].y;
					vector.z = mesh->mTangents[i].z;
					vertex.Tangent = vector;
					// bitangent
					vector.x = mesh->mBitangents[i].x;
					vector.y = mesh->mBitangents[i].y;
					vector.z = mesh->mBitangents[i].z;
					vertex.Bitangent = vector;
					*/
				}
				else
					vertex.TexCoords = glm::vec2(0.4f, 0.4f);

				vertices.push_back(vertex);
			}
			// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
			for(unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for(unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);        
			}
			return Mesh(vertices, indices);
	}
	inline struct Model {
		std::vector<Mesh> meshes;
		std::vector<Transform> transformations;
	} mainModel;
	
	
	inline Model processNode(aiNode *node, const aiScene *scene) {
		
		// process each mesh located at the current node
		std::cout << "Process Node" << std::endl;
		for(unsigned int i = 0; i < node->mNumMeshes; i++) {
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			mainModel.meshes.push_back(processMesh(mesh, scene));
			aiVector3D pScaling, pRotation, pPosition;
			node->mTransformation.Decompose(pScaling, pRotation, pPosition);
			Transform t = Transform( vec3_cast(pPosition), vec3_cast(pRotation), vec3_cast(pScaling));
			mainModel.transformations.push_back(t);
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for(unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}

		return mainModel;
	}

	inline std::vector<Mesh> processModel(const aiScene *scene) {
		std::vector<Mesh> meshes;
		// process each mesh located at the current node
		for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[i];
			
			meshes.push_back(processMesh(mesh, scene));
		}
		return meshes;
	}

	inline void SeriousModel (aiNode *node, const aiScene *scene) {
		
		for(unsigned int i = 0; i < node->mNumMeshes; i++) {
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			mainModel.meshes.push_back(processMesh(mesh, scene));
			aiVector3D pScaling, pRotation, pPosition;
			node->mTransformation.Decompose(pScaling, pRotation, pPosition);
			Transform t = Transform( vec3_cast(pPosition), vec3_cast(pRotation), vec3_cast(pScaling));
			mainModel.transformations.push_back(t);
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for(unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}
}