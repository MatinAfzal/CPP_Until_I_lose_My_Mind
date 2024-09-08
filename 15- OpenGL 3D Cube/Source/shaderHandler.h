#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cerrno>

std::string getFileRaw(const char* fileName);

class ShaderHandler {
	public:
		GLuint ID;
		ShaderHandler(const char* vertexFile, const char* fragmentFile);
		void activate(void);
		void deactive(void);
	private:
		void errorHandler(unsigned int shader, const char* type);
};

#endif