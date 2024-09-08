#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind(void) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind(void) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deactive(void) {
	glDeleteBuffers(1, &ID);
}