//main.cpp setup by River

#include <stdio.h>
#include <math.h>

#include <lib/external/glad.h>
#include <lib/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

#include <lib/texture.h>
#include <lib/shader.h>

struct Vertex {
	float x, y, z;
	float u, v;
};

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned short* indicesData, int numIndices);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
unsigned int swap(unsigned int current, unsigned int dragonTexture1, unsigned int dragonTexture2);

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

Vertex vertices[4] = {
	{-1.0, -1.0, 0.0, 0.0, 0.0},
	{1.0, -1.0, 0.0, 1.0, 0.0},
	{1.0, 1.0, 0.0, 1.0, 1.0},
	{-1.0, 1.0, 0.0, 0.0, 1.0}
};
unsigned short indices[6] = {
	0, 1, 2,
	2, 3, 0
};

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Final Project", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	ew::Shader backgroundShader("assets/background.vert", "assets/background.frag");

	ew::Shader dragonShader("assets/dragon.vert", "assets/dragon.frag");
	unsigned int dragonTexture1 = ew::loadTexture("assets/dragon1.png", GL_REPEAT, GL_NEAREST);
	unsigned int dragonTexture2 = ew::loadTexture("assets/dragon2.png", GL_REPEAT, GL_NEAREST);

	unsigned int quadVAO = createVAO(vertices, 4, indices, 6);

	int index = 1;
	unsigned int texture = dragonTexture1;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(quadVAO);

		float time = (float)glfwGetTime();

		//background shader
		backgroundShader.use();

		//set uniforms
		backgroundShader.setFloat("_Time", time);
		backgroundShader.setVec3("_HillColor", ew::Vec3(0.1, 0.1, 0.1));

		//draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		//dragon shader by River
		dragonShader.use();

		if (index % 10 == 0) {
			texture = swap(texture, dragonTexture1, dragonTexture2);
		}
		index++;

		//bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		//set uniforms
		dragonShader.setInt("_DragonTexture", 0);

		//draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned short* indicesData, int numIndices) {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//Vertex Buffer Object 
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, vertexData, GL_STATIC_DRAW);
	//Element Buffer Object
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * numIndices, indicesData, GL_STATIC_DRAW);
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, x));
	glEnableVertexAttribArray(0);
	//UV attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, u)));
	glEnableVertexAttribArray(1);
	return vao;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//swap function by River
unsigned int swap(unsigned int current, unsigned int dragonTexture1, unsigned int dragonTexture2) {
	if (current == dragonTexture1) {
		return dragonTexture2;
	}
	else { return dragonTexture1; }
}