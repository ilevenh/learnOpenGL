#pragma once
//用两个不同shader绘制两个三角形

#include "homeworkbase.h"
#include "shader.h"

NS_HW_BEGIN
class Homework01 : public HomeWorkBase
{
public:
	void init();
	void render();

	GLuint _vao1, _vao2; //两个vao
	Shader * _shader1, * _shader2; //两个shader program
};
float hw01firstVertex[] = {
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
};
float hw01secondVertex[] = {
	-0.3f, 0.2f, 0.0f,  // left
	0.9f, 0.2f, 0.0f,  // right
	0.1f, -0.6f, 0.0f   // top 
};

void Homework01::init()
{
	//1.创建2个vao
	glGenVertexArrays(1, &_vao1);
	glGenVertexArrays(1, &_vao2);
	//2.创建第一个三角形的渲染vbo
	//2.1 绑定vao
	glBindVertexArray(_vao1);
	//2.2 顶点数组复制到一个顶点缓冲中，供OpenGL使用
	GLuint vbo1;
	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hw01firstVertex), hw01firstVertex, GL_STATIC_DRAW);
	//2.3 设置顶点属性指针, 并启用顶点属性，传入的0是顶点属性位置值，
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	//3.第二个三角形
	glBindVertexArray(_vao2);
	GLuint vbo2;
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hw01secondVertex), hw01secondVertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	//创建shader
	_shader1 = new Shader("hw\\01\\01.vs", "hw\\01\\01.fs");
	_shader2 = new Shader("hw\\01\\02.vs", "hw\\01\\02.fs");
}

void Homework01::render()
{
	//在render外已经初始化了vao， 创建了shader

	//清除颜色缓冲
	glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//7.first 
	float timeVal = glfwGetTime();
	_shader1->use();
	_shader1->setFloat("ourColor1", cos(timeVal) / 2.0f + 0.5f);
	_shader1->setFloat("ourColor2", sin(timeVal) / 2.0f + 0.5f);
	glBindVertexArray(_vao1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//6.second
	_shader2->use();
	_shader2->setFloat("offset", cos(timeVal) / 2.0f + 0.5f);
	glBindVertexArray(_vao2);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

NS_HW_END

