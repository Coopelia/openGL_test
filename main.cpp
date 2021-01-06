#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

float vertices[] =
{
	//       位置                   法向        贴图坐标
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] =
{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f)
};

glm::vec3 cubeScale = glm::vec3(1.0f, 1.0f, 1.0f);
float cubeAngel = 0.0f;

int fram = 0;//第几帧
bool isPlay = false;

void PlayAnimate()
{
	fram++;
	if (fram > 50)
		fram = 50;
	if (fram < 50) //前50帧向外发散
	{
		for (int i = 1; i < 9; i++)
		{
			cubePositions[i].x += 0.1 * cos(0.25 * i * 3.1415926);
			cubePositions[i].z += 0.1 * sin(0.25 * i * 3.1415926);
		}
	}
	else //后面一直做旋转
	{
		cubeAngel += 1.0f;
	}
}

float deltaTime = 0.0f;  //两帧之间的间隔时间
float lastFrame = 0.0f;  //上一帧绘制的时间

float lastX = 400, lastY = 300;
bool firstMouse = true;
float yaw = 0.0f, pitch = 0.0f;

glm::vec3 light_ambient = glm::vec3(0.2f, 0.2f, 0.2f);//环境光
glm::vec3 light_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);//漫反射
glm::vec3 light_specular = glm::vec3(1.0f, 1.0f, 1.0f);//高光

Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));

void loadTexture(unsigned int& texture, const char* path)
{
	texture = -1;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//设置纹理包装和过滤的方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "加载贴图文件失败" << std::endl;
	stbi_image_free(data);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//获取最大属性数量
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "最大支持的属性数量为：" << nrAttributes << std::endl;

	glEnable(GL_DEPTH_TEST);

	Shader lamp_shader("lamp.vs", "lamp.fs");

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//加载纹理
	unsigned int diffuseMap;
	glActiveTexture(GL_TEXTURE1);
	loadTexture(diffuseMap, "1.jpg");

	unsigned int specularMap;
	glActiveTexture(GL_TEXTURE2);
	loadTexture(specularMap, "2.png");

	//采样器绑定纹理单元
	lamp_shader.use();
	lamp_shader.setInt("material.diffuse", diffuseMap);
	lamp_shader.setInt("material.specular", specularMap);

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		lamp_shader.use();

		lamp_shader.setVec3("viewPos", camera.Position);
		lamp_shader.setVec3("light.ambient", light_ambient);
		lamp_shader.setVec3("light.diffuse", light_diffuse);
		lamp_shader.setVec3("light.specular", light_specular);
		lamp_shader.setFloat("light.constant", 1.0f);
		lamp_shader.setFloat("light.linear", 0.09f);
		lamp_shader.setFloat("light.quadratic", 0.032f);
		lamp_shader.setVec3("light.position", camera.Position);
		lamp_shader.setVec3("light.direction", camera.Front);
		lamp_shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		lamp_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		lamp_shader.setFloat("material.shininess", 32.0f);
		
		//投影矩阵
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		lamp_shader.setMat4("projection", glm::value_ptr(projection));
		//观察矩阵
		glm::mat4 view;
		view = camera.GetViewMatrix();
		lamp_shader.setMat4("view", glm::value_ptr(view));
		
		if(isPlay)
			PlayAnimate();

		glBindVertexArray(VAO);
		for (int i = 0; i < 9; ++i)
		{
			//模型矩阵
			glm::mat4 model;
			if (i == 0)
			{
				model = glm::translate(model, cubePositions[0]);
				model = glm::rotate(model, glm::radians(cubeAngel), glm::vec3(0, 1, 0));
			}
			else
			{
				model = glm::translate(model, cubePositions[i] - cubePositions[i - 1]);
				model = glm::rotate(model, glm::radians(cubeAngel), glm::vec3(0, 1, 0));
			}
			lamp_shader.setMat4("model", glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//摄像机
		glm::mat4 model3;
		model3 = glm::translate(model3, camera.GetCamLoc() + glm::vec3(0.0f, 0.2f, 0.0f));
		model3 = glm::rotate(model3, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model3 = glm::rotate(model3, glm::radians(camera.Yaw), glm::vec3(0.0f, 0.0f, 1.0f));
		model3 = glm::rotate(model3, glm::radians(camera.Pitch), glm::vec3(1.0f, 0.0f, 0.0f));

		model3 = glm::scale(model3, glm::vec3(0.5, 2.0, 1.0));
		lamp_shader.setMat4("model", glm::value_ptr(model3));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_R)== GLFW_PRESS)
		light_ambient += 0.1;

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		light_ambient -= 0.1;

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		light_diffuse += 0.1;

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		light_diffuse -= 0.1;

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		light_specular += 0.1;

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		light_specular -= 0.1;

	if (glfwGetKey(window, GLFW_KEY_P) ==	GLFW_PRESS)
		isPlay = true;

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		isPlay = false;

	float xoffset = 0, yoffset = 0;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		yoffset = 5;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		yoffset = -5;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		xoffset = 5;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		xoffset = -5;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = lastX - xPos;
	float yoffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

//鼠标滚轮消息回调
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
