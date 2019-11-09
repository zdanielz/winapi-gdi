#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;

void CreatRect(HDC dc, int nx, int ny, int SizeOfPart, int width, int height, int padding, HBITMAP hbm) {
	const int size = 4;
	POINT p[size];

	p[0] = { nx + (padding * nx + nx * SizeOfPart), ny + (padding * ny + ny * SizeOfPart) };
	p[1] = { nx + SizeOfPart + (padding * nx + nx * SizeOfPart), ny + (padding * ny + ny * SizeOfPart) };
	p[2] = { nx + SizeOfPart + (padding * nx + nx * SizeOfPart), ny + SizeOfPart + (padding * ny + ny * SizeOfPart) };
	p[3] = { nx + (padding * nx + nx * SizeOfPart), ny + SizeOfPart + (padding * ny + ny * SizeOfPart) };

	Polygon(dc, p, size);
}

int main(void) {
	srand(time(NULL));

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	int SizeOfPart = 6;
	int padding = 1;

	HDC dc = GetDC(NULL);
	HWND hWnd = GetDesktopWindow();


	HDC dcCompatible = CreateCompatibleDC(dc);
	HBITMAP hbm = CreateCompatibleBitmap(dc, width, height);

	SelectObject(dcCompatible, hbm);
	HBRUSH hBrush;

	COLORREF color = RGB(50, 50, 50);
	hBrush = CreateSolidBrush(color);
	SelectObject(dcCompatible, hBrush);

	for (size_t y = 0; y < height / (SizeOfPart + padding); y++) {
		for (size_t x = 0; x < width / (SizeOfPart + padding); x++) {
			CreatRect(dcCompatible, x, y, SizeOfPart, width, height, padding, hbm);
		}
	}

	for (int i = 0; i < 10000; i++) {
		COLORREF color = RGB(rand() % 255, rand() % 255, rand() % 255);
		hBrush = CreateSolidBrush(color);
		SelectObject(dcCompatible, hBrush);
		CreatRect(dcCompatible, rand() % width / (SizeOfPart + padding), rand() % height / (SizeOfPart + padding), SizeOfPart, width, height, padding, hbm);
		BitBlt(dc, 0, 0, width, height, dcCompatible, 0, 0, SRCCOPY);
		DeleteObject(hBrush);
	}

	return 0;
}
