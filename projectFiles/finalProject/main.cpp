#include <stdio.h>
#include <math.h>

#include <lib/external/glad.h>
#include <lib/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

#include <lib/texture.h>
#include <lib/shader.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

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

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	ew::Shader dragonShader("assets/dragon.vert", "assets/dragon.frag");
	//unsigned int dragonTexture = loadTexture("assets/TITLE.png", GL_REPEAT, GL_NEAREST);
	ew::Shader backgroundShader("assets/background.vert", "assets/background.frag");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//background shader
		backgroundShader.use();

		//character shader
		dragonShader.use();

		//bind texture
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, dragonTexture);
		
		//set uniforms
		dragonShader.setInt("_DragonTexture", 0);

		//draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
