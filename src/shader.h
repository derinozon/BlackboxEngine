#pragma once

#ifdef __EMSCRIPTEN__
	#include <GL/gl.h>
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "internal/res_shader.h"

std::string get_file_contents(const char* filename);

class Shader {
	public:
		GLuint ID;
		
		Shader();
		Shader(const char* shaderSource, GLuint shaderType);
		Shader(const char* vertexFile, const char* fragmentFile);

		void UploadUniform3f (const char* uniform, glm::vec3 vector);
		void UploadUniform4f (const char* uniform, glm::vec4 vector);
		void UploadUniform1i (const char* uniform, int i);
		void UploadUniformMatrix4fv (const char* uniform, glm::mat4 matrix);
		void Activate();
		void Delete();
	private:
		void CompileErrors (unsigned int shader, const char* type);
		GLuint CreateShader (const char* shaderSource, GLuint shaderType);
};