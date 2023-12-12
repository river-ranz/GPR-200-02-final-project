//main.cpp setup by River

#include <stdio.h>
#include <math.h>

#include <lib/external/glad.h>
#include <lib/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <lib/texture.h>
#include <lib/shader.h>

struct Vertex {
	float x, y, z;
	float u, v;
};

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned short* indicesData, int numIndices);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

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
	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ew::Shader backgroundShader("assets/background.vert", "assets/background.frag");
	unsigned int mountainTexture1 = ew::loadTexture("assets/Mountain1.png", GL_REPEAT, GL_NEAREST);
	unsigned int mountainTexture2 = ew::loadTexture("assets/Mountain2.png", GL_REPEAT, GL_NEAREST);
	unsigned int cloudTexture1 = ew::loadTexture("assets/Clouds1.png", GL_REPEAT, GL_NEAREST);
	float flightSpeed = 1.25;
	float mountain1Start = 0;
	float mountain2Start = 0;
	float clouds1Start = 0;

	ew::Shader dragonShader("assets/dragon.vert", "assets/dragon.frag");
	unsigned int dragonSpriteSheet = ew::loadTexture("assets/spriteSheet.png", GL_REPEAT, GL_NEAREST);

	unsigned int quadVAO = createVAO(vertices, 4, indices, 6);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(quadVAO);

		float time = (float)glfwGetTime();

		//background shader
		backgroundShader.use();

		backgroundShader.setFloat("_Time", time);
		backgroundShader.setFloat("_backgroundSpeed", flightSpeed);
		backgroundShader.setVec4("_HillColor", ew::Vec4(0.2, 0.7, 0.2, 1.0));

		// Mountain 1 -- By Liam
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mountainTexture1);
		backgroundShader.setInt("_Texture", mountainTexture1);
		backgroundShader.setInt("_ImageID", 2);
		backgroundShader.setFloat("_SpriteStartPos", clouds1Start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		// Mountain 2 -- By Liam
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, mountainTexture2);
		backgroundShader.setInt("_Texture", mountainTexture2);
		backgroundShader.setInt("_ImageID", 3);
		backgroundShader.setFloat("_SpriteStartPos", mountain1Start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		// Clouds -- By Liam
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, cloudTexture1);
		backgroundShader.setInt("_Texture", cloudTexture1);
		backgroundShader.setInt("_ImageID", 1);
		backgroundShader.setFloat("_SpriteStartPos", mountain2Start);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		//dragon shader by River
		dragonShader.use();

		//bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, dragonSpriteSheet);
		
		//set uniforms
		dragonShader.setFloat("_Time", time);
		dragonShader.setInt("_DragonTexture", 0);

		//draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//UI by Liam
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");

			ImGui::DragFloat("Speed", &flightSpeed, 0.05f);
			ImGui::DragFloat("Cloud Start Position", &clouds1Start, 0.05f);
			ImGui::DragFloat("Mountain 1 Start Position", &mountain1Start, 0.05f);
			ImGui::DragFloat("Mountain 2 Start Position", &mountain2Start, 0.05f);

			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

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