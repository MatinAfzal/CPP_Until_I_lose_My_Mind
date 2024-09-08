#include "Textures.h"

Texture::Texture(const char* fileName, GLenum tType, GLenum slot, GLenum format, GLenum pixelType) {

	type = tType;
	int textureWidth, textureHeight, textureColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(fileName, &textureWidth, &textureHeight, &textureColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(tType, ID);

	glTexParameteri(tType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(tType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(tType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(tType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(tType, 0, GL_RGBA, textureWidth, textureHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(tType);

	stbi_image_free(bytes);
	glBindTexture(tType, 0);
}

void Texture::activate(ShaderHandler& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.activate();
	glUniform1i(texUni, unit);
}

void Texture::bind()
{
	glBindTexture(type, ID);
}

void Texture::unbind()
{
	glBindTexture(type, 0);
}

void Texture::deactive()
{
	glDeleteTextures(1, &ID);
}