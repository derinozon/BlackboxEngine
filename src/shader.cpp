#include "shader.h"

namespace Blackbox {

	std::string get_file_contents(const char* filename) {
		std::ifstream in(filename, std::ios::binary);
		if (in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		throw(errno);
	}

	GLuint Shader::CreateShader (const char *shaderSource, GLuint shaderType) {
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		std::string errType;
		switch (shaderType) {
		case GL_VERTEX_SHADER:
			errType = "VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			errType = "FRAGMENT";
			break;
		case GL_COMPUTE_SHADER:
			errType = "COMPUTE";
			break;
		default:
			errType = "UNDEFINED";
			break;
		}
		CompileErrors(shader, errType.c_str());
		return shader;
	}

	Shader::Shader(){};

	Shader::Shader(const char *shaderSource, GLuint shaderType){
		GLuint shader = CreateShader(shaderSource, shaderType);

		ID = glCreateProgram();
		glAttachShader(ID, shader);
		glLinkProgram(ID);
		CompileErrors(ID, "PROGRAM");
		glDeleteShader(shader);
	};

	Shader::Shader(const char* vertexSource, const char* fragmentSource) {
		GLuint vertexShader = CreateShader(vertexSource, GL_VERTEX_SHADER);
		GLuint fragmentShader = CreateShader(fragmentSource, GL_FRAGMENT_SHADER);

		ID = glCreateProgram();

		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);

		glLinkProgram(ID);

		CompileErrors(ID, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::Activate() {
		glUseProgram(ID);
	}

	void Shader::Delete() {
		glDeleteProgram(ID);
	}

	void Shader::UploadUniform3f (const char* uniform, glm::vec3 vector) {
		GLuint texUni = glGetUniformLocation(ID, uniform);
		Activate();
		glUniform3f(texUni, vector.x, vector.y, vector.z);
	}

	void Shader::UploadUniform4f (const char* uniform, glm::vec4 vector) {
		GLuint texUni = glGetUniformLocation(ID, uniform);
		Activate();
		glUniform4f(texUni, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::UploadUniform1i (const char* uniform, int i) {
		GLuint texUni = glGetUniformLocation(ID, uniform);
		Activate();
		glUniform1i(texUni, i);
	}

	void Shader::UploadUniformMatrix4fv (const char* uniform, glm::mat4 matrix) {
		GLuint texUni = glGetUniformLocation(ID, uniform);
		Activate();
		glUniformMatrix4fv(texUni, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::CompileErrors(unsigned int shader, const char* type) {
		GLint hasCompiled;
		char infoLog[1024];

		if (strcmp(type, "PROGRAM") != 0) {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				LogError("Error Compiling Shader: ", type, "\n", infoLog);
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				LogError("Error Linking Shader: ", type, "\n", infoLog);
			}
		}
	}
}
