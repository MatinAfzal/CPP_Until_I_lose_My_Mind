#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderHandler.h"

class Texture {
	public:
		GLuint ID;
		GLenum type;
		Texture(const char* fileName, GLenum type, GLenum slot, GLenum format, GLenum pixelType);
		void activate(ShaderHandler &shader, const char* uniform, GLuint uint);
		void bind();
		void unbind();
		void deactive();
};

#endif