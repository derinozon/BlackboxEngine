#pragma once

#ifdef __EMSCRIPTEN__
	static const char* DEFAULT_UNLIT_VERT = R"(#version 300 es

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;
		layout (location = 2) in vec2 aTex;

		out vec3 vColor;
		out vec2 texCoord;

		uniform mat4 _MVP;

		void main() {
			gl_Position = _MVP * vec4(aPos, 1.0);
			vColor = aColor;
			texCoord = aTex;
		}
	)";
	static const char* DEFAULT_UNLIT_FRAG = R"(#version 300 es

		precision mediump float; 

		out vec4 FragColor;

		in vec3 vColor;
		in vec2 texCoord;

		uniform sampler2D tex0;
		uniform vec4 color;

		void main() {
			FragColor = texture(tex0, texCoord) * color;
		}
	)";
#else
	static const char* DEFAULT_UNLIT_VERT = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;
		layout (location = 2) in vec2 aTex;

		out vec3 vColor;
		out vec2 texCoord;

		uniform mat4 _MVP;

		void main() {
			gl_Position = _MVP * vec4(aPos, 1.0);
			vColor = aColor;
			texCoord = aTex;
		}
	)";
	static const char* DEFAULT_UNLIT_FRAG = R"(
		#version 330 core

		out vec4 FragColor;

		in vec3 vColor;
		in vec2 texCoord;

		uniform sampler2D tex0;
		uniform vec4 color;

		void main() {
			FragColor = texture(tex0, texCoord) * color;
		}
	)";
#endif