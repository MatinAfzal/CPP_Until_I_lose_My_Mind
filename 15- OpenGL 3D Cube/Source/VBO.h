#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
	public:
		GLuint ID;
		VBO(GLfloat* vertices, GLsizeiptr size);
		void bind(void);
		void unbind(void);
		void deactive(void);
};

#endif