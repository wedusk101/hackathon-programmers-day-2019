#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

const int width = 120, height = 40, bufferSize = height * width;
wchar_t *frameBuffer = new wchar_t[bufferSize];
DWORD bytesWritten = 0;
HANDLE hAppWnd = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

struct Vec2
{
	double x, y;
	Vec2() : x(0), y(0) {}
	Vec2(const double &x_, const double &y_) : x(x_), y(y_) {}

	void draw(char ch)
	{ 
		frameBuffer[(int)y * height + (int)x] = ch;
		WriteConsoleOutputCharacter(hAppWnd, (LPCTSTR)frameBuffer, bufferSize, { 0, 0 }, &bytesWritten);
	}
};

void clearFrameBuffer()
{ 
	for (int i = 0; i < bufferSize; i++)
		frameBuffer[i] = ' ';
	frameBuffer[bufferSize - 1] = '\0';
	WriteConsoleOutputCharacter(hAppWnd, (LPCTSTR)frameBuffer, bufferSize, { 0, 0 }, &bytesWritten);
}

struct Paddle
{
	Vec2 top, bottom, middle;
	Paddle(const Vec2 &top_) : top(top_)
	{ 
		middle = Vec2(top.x, top.y);
		bottom = Vec2(top.x , top.y);
	}

	void draw()
	{
		int ch = 0xB2;
		top.draw(ch);
		middle.draw(ch);
		bottom.draw(ch);
	}
};

int main()
{
	SetConsoleActiveScreenBuffer(hAppWnd); clearFrameBuffer();
	Vec2 src = Vec2(0, 0);
	Vec2 dst = Vec2(0, 40);
	Paddle leftPaddle(Vec2(0, 19));
	bool isSpace = false;

	while (true)
	{
		src.draw('*');
		dst.draw('*');
		leftPaddle.draw();
		if (GetAsyncKeyState(VK_SPACE))
			clearFrameBuffer();
	}

	delete[] frameBuffer;
}