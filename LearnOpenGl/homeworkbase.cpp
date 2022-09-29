#include "homeworkbase.h"


NS_HW_BEGIN

void HomeWorkBase::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 0.1f); //状态设置函数
	glClear(GL_COLOR_BUFFER_BIT); //状态使用函数
}

NS_HW_END