#ifndef __HOMEWORK_BASE_H__
#define __HOMEWORK_BASE_H__
#define NS_HW_BEGIN namespace homework {
#define NS_HW_END	}
#define NS_HW homework::

#include <glad/glad.h>
#include <GLFW/glfw3.h>

NS_HW_BEGIN
class HomeWorkBase
{
public:
	HomeWorkBase() {};
	~HomeWorkBase() {};

	//��ʼ��vao ������
	virtual void init() {};
	//��Ⱦָ�� 
	virtual void render();

};
NS_HW_END

#endif