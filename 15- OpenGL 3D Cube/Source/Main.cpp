#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderHandler.h"
#include "Textures.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

const char* screenTitle = "OpenGL 3D Cube";
float bgColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

int main() {

	// Objects
	GLfloat vertices[] =
	{
		// Front face
		-0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,

		// Back face
		0.5f, -0.5f, 0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
	   -0.5f, -0.5f, 0.5f,   0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
	   -0.5f,  0.5f, 0.5f,   0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
		0.5f,  0.5f, 0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 1.0f,

		// Left face
		-0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,

		// Right face
		0.5f, -0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 1.0f,

		// Top face
		-0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
		 0.5f,  0.5f
	};

	GLuint indices[] =
	{
		// Front face
		0, 1, 2,
		0, 2, 3,

		// Back face
		4, 5, 6,
		4, 6, 7,

		// Left face
		8, 9, 10,
		8, 10, 11,

		// Right face
		12, 13, 14,
		12, 14, 15,

		// Top face
		16, 17, 18,
		16, 18, 19,

		// Bottom face
		20, 21, 22,
		20, 22, 23
	};



	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, screenTitle, NULL, NULL);
	if (window == NULL) {
		std::cerr << "Unable to create GLFWwindow" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Shaders
	ShaderHandler shaderProgram("d_vert.vert", "d_frag.frag");

	// VAO & VBO & EBO
	VAO VAO_1;
	VAO_1.bind();

	VBO VBO_1(vertices, sizeof(vertices));
	EBO EBO_1(indices, sizeof(indices));

	VAO_1.LinkAttrib(VBO_1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO_1.LinkAttrib(VBO_1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO_1.LinkAttrib(VBO_1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO_1.unbind();
	VBO_1.unbind();
	EBO_1.unbind();

	GLuint uniformID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture textureKishibe("tile125.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	textureKishibe.activate(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.activate();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 40.5f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.1f, -250.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1i(uniformID, 0.5f);
		textureKishibe.bind();
		VAO_1.bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO_1.deactive();
	VBO_1.deactive();
	EBO_1.deactive();
	textureKishibe.deactive();
	shaderProgram.deactive();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}