#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
const int width = 320, height = 240, bufferSize = height * width; wchar_t *frameBuffer = new wchar_t[bufferSize]; DWORD bytesWritten = 0;
HANDLE hAppWnd = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
struct Vec2 {
	double x; double y;	Vec2() : x(0), y(0) {} 
	Vec2(const double &x_, const double &y_) : x(x_), y(y_) {}
	void draw() { WriteConsoleOutputCharacter(hAppWnd, (LPCTSTR)frameBuffer, bufferSize, { x, y }, &bytesWritten); }
};
struct Circle {
	Vec2 center; double radius;
	Circle(const Vec2 &c_, const double &r_) : center(c_), radius(r_) {}
	void draw()	{

	}
};
struct Line {
	Vec2 src; Vec2 dst;
	Line(const Vec2 &src_, const Vec2&dst_) : src(src_), dst(dst_) {}
	void draw() {

	}
};
struct Rectangle {
	Vec2 topLeft; Vec2 bottomRight;
	Rectangle(const Vec2 &tl_, const Vec2&br_) : topLeft(tl_), bottomRight(br_) {}
	void draw() {
		Vec2 bottomLeft = Vec2(topLeft.x, bottomRight.y); Vec2 topRight = Vec2(topLeft.y, bottomRight.x);
		Line top = Line(topLeft, topRight); Line bottom = Line(bottomLeft, bottomRight); Line left = Line(topLeft, bottomLeft); Line right = Line(topRight, bottomRight);
		top.draw(); bottom.draw(); left.draw(); right.draw();
	}
};
int main(int argc, char *argv[]) {
	
	SetConsoleActiveScreenBuffer(hAppWnd);
	frameBuffer[bufferSize - 1] = '\0';
	
}