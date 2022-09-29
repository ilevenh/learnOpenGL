#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "homeworkbase.h"

class Window
{
public:
	Window(int height = 800, int width = 600);
	~Window();

	/*渲染主循环*/
	void run();
	void initHomeWork(NS_HW HomeWorkBase *);

private:
	void init();
	void createWindow();
	void initGlad();
	void registerCallback();

public:
	GLFWwindow * window; //窗口对象
	NS_HW HomeWorkBase * hw; //hw对象 

private:
	int _width;
	int _height;


};


#endif