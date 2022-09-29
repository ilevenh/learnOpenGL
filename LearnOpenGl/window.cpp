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
		//4.�ӿڣ�OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)
		glViewport(0, 0, _width, _height);
		//5.ע�ᣬ���ڴ�С�䶯�Ļص�����
		registerCallback();
		//
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //�߿�ģʽ����������

	} while (0);
}

Window::~Window()
{

}

//��Ⱦ��ѭ��
void Window::run()
{
	auto processInput = [&]() {
		//�����window�����ڰ���esc�����ͻ�����shouldcloseΪtrue
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	};
	//note 6.��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//����
		processInput(); //�������е����� 

		//��Ⱦָ��
		hw->render();

		//��鲢�����¼�����������
		glfwPollEvents();//�����û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwSwapBuffers(window);//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
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
