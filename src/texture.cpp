#include "texture.h"
#include "debug.h"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

// Loads texture from path
Texture::Texture(const char* image, GLenum texType) {
	type = texType;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &width, &height, &colorChannels, 0);
	
	if (!data) {
		Log("Problem loading texture");
	}

	GenerateGLTexture(data);
	stbi_image_free(data);
}

// Creates texture from custom bytes
Texture::Texture(unsigned char bytes[], int widthImg, int heightImg, int numColCh, GLenum texType = GL_TEXTURE_2D) {
	type = texType;

	if (!bytes) {
		Log("Problem loading texture");
	}
	width = widthImg; height = heightImg; colorChannels = numColCh;
	GenerateGLTexture(bytes);
}

// Loads texture from memory
Texture::Texture(unsigned char bytes[], int len, int desiredChannels, GLenum texType) {
	type = texType;
	stbi_set_flip_vertically_on_load(true);

	stbi_uc* data = stbi_load_from_memory(bytes, len, &width, &height, &colorChannels, desiredChannels);
	if (!data) {
		Log("Problem loading texture");
	}
	GenerateGLTexture(data);
	stbi_image_free(data);
}

void Texture::GenerateGLTexture (unsigned char data[], GLenum texType) {
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	GLint cc = colorChannels > 3 ? GL_RGBA : GL_RGB;
	glTexImage2D(texType, 0, cc, width, height, 0, cc, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texType);

	glBindTexture(texType, 0);
}

// void Texture::GetPixelData() {
// 	GLuint fbo;
// 	glGenFramebuffers(1, &fbo);
// 	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

// 	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ID, 0);

// 	// Create a PBO
// 	GLuint pbo;
// 	glGenBuffers(1, &pbo);
// 	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
// 	glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 4, nullptr, GL_STREAM_READ);
// 	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

// 	// Read the pixels from the framebuffer into the PBO
// 	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
// 	glReadBuffer(GL_COLOR_ATTACHMENT0);
// 	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
// 	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
// 	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
// 	glBindFramebuffer(GL_FRAMEBUFFER, 0);

// 	// Map the PBO
// 	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
// 	GLubyte* pixels = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

// 	// Save the image using stb_image_write
// 	stbi_write_png("output.png", width, height, 4, pixels, width * 4);

// 	// Unmap the PBO
// 	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
// 	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

// }

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &ID);
	Log("Deleting Texture");
}