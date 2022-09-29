#include <iostream>
#include "window.h"


Window::Window(int height /*= 800*/, int width /*= 600*/)
	:_width(width),
	_height(height)
{
	do
	{
		//1.init
		init();
		//2.create window
		createWindow();
		//3.init glad
		initGlad();
		//4.视口，OpenGL渲染窗口的尺寸大小，即视口(Viewport)
		glViewport(0, 0, _width, _height);
		//5.注册，窗口大小变动的回调函数
		registerCallback();
		//
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式绘制三角形

	} while (0);
}

Window::~Window()
{

}

//渲染主循环
void Window::run()
{
	auto processInput = [&]() {
		//如果在window窗口内按下esc键，就会设置shouldclose为true
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	};
	//note 6.渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(); //处理所有的输入 

		//渲染指令
		hw->render();

		//检查并调用事件，交换缓冲
		glfwPollEvents();//检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
		glfwSwapBuffers(window);//函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
	}
	glfwTerminate();
}

void Window::initHomeWork(NS_HW HomeWorkBase * _hw)
{
	hw = _hw;
	hw->init();
}

void Window::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::createWindow()
{
	window = glfwCreateWindow(800, 600, "window", NULL, NULL);
	if (window == nullptr)
	{
		printf_s("failed to create glfw window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
}

void Window::initGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf_s("failed to init glad");
	}
}

void Window::registerCallback()
{
	auto frameBufferSizeCallback = [](GLFWwindow * w, int width, int height) -> void {
		glViewport(0, 0, width, height);
	};
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
}
