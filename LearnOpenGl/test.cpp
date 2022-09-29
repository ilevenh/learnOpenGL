#include <iostream>
#include "window.h"
#include "homeworkbase.h"
#include "01draw2triangles.h"
#include "02moreVertexAttrTriangles.h"

int main()
{
	Window * window = new Window();
	NS_HW HomeWorkBase * hw = new NS_HW Homework02();
	window->initHomeWork(hw);
	window->run();
}


