#pragma once
/**
 * 用两个顶点属性（位置，颜色）来画三角形
 */
#include "homeworkbase.h"

NS_HW_BEGIN
class Homework02 : public HomeWorkBase
{
public:
	void init();
	void render();

	GLuint vao;
	Shader * shader;
};

float verticeshw02[] = {
	// 位置              // 颜色
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};

void Homework02::init()
{
	//1.
	glGenVertexArrays(1, &vao);
	//2.绑定vao， 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticeshw02), verticeshw02, GL_STATIC_DRAW);
	//3.绑定到指针
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	//颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shader = new Shader("hw\\02\\01.vs", "hw\\02\\01.fs");
}

void Homework02::render()
{
	//清除颜色缓冲
	glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//6.使用shader
	shader->use();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

NS_HW_END