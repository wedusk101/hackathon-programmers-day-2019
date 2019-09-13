#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
const int width = 240, height = 180, bufferSize = height * width; wchar_t *frameBuffer = new wchar_t[bufferSize]; DWORD bytesWritten = 0;
HANDLE hAppWnd = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
struct Vec2 {
	double x; double y;	Vec2() : x(0), y(0) {} 
	Vec2(const double &x_, const double &y_) : x(x_), y(y_) {}
	void draw() { WriteConsoleOutputCharacter(hAppWnd, (LPCTSTR)frameBuffer, bufferSize, { (short)x, (short)y }, &bytesWritten); }
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
	void draw() { // DDA line drawing algorithm
		double slope = 0.0, x = 0.0, y = 0.0;
		int dy = dst.y - src.y, dx = dst.x - src.x, sgn = 0;
		if (dx == 0)
			for (y = src.y; y <= dst.y; ++y) { Vec2 p(x, y); p.draw(); }
		else if (dy == 0)
			for (x = src.x; x <= dst.x; ++x) { Vec2 p(x, y); p.draw(); }
		else {
			if (abs(dy) <= abs(dx)) { // gentle slope
				if (src.x > dst.x) // swaps the srcing point if needed
					swap(src, dst);
				src.draw();	slope = dy / (double)dx; sgn = sign(slope);
				for (x = src.x, y = src.y; x <= dst.x; x += sgn) {y += slope;	Vec2 p(x, y); p.draw();}}
			else { // steep slope
				if (src.y > dst.y) // swaps the srcing point if needed
					swap(src, dst);
				dst.draw(); slope = dx / (double)dy; sgn = sign(slope);
				for (x = src.x, y = src.y; y <= dst.y; y += sgn) { x += slope; Vec2 p(x, y); p.draw();}}}}
};
struct Rectangle {
	Vec2 topLeft; Vec2 bottomRight;
	Rectangle(const Vec2 &tl_, const Vec2&br_) : topLeft(tl_), bottomRight(br_) {}
	void draw() {
		Vec2 bottomLeft = Vec2(topLeft.x, bottomRight.y); Vec2 topRight = Vec2(topLeft.y, bottomRight.x);
		Line top = Line(topLeft, topRight); Line bottom = Line(bottomLeft, bottomRight); Line left = Line(topLeft, bottomLeft); Line right = Line(topRight, bottomRight);
		top.draw(); bottom.draw(); left.draw(); right.draw();}
};
void swap(Vec2 &a, Vec2 &b){Vec2 tmp = a; a = b; b = tmp;}
int sign(const double &val) { return (val == 0) ? 0 : (val < 0) ? -1 : 1;}
int main() {	
	SetConsoleActiveScreenBuffer(hAppWnd);
	frameBuffer[bufferSize - 1] = '\0';	

	delete [] frameBuffer;
}