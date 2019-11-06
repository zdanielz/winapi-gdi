#include <windows.h>
#include <iostream>
using namespace std;

void CreatRect(HDC dc, int nx, int ny, int SizeOfPart, int width, int height, int padding, int number, HBITMAP hbm) {
	SelectObject(dc, hbm);
	COLORREF color = RGB(226, 124, 62);


	const int size = 4;
	POINT p[size];

	HBRUSH hBrush;
	hBrush = CreateSolidBrush(color);
	SelectObject(dc, hBrush);

	p[0] = { nx * number + padding, ny * number + padding };
	p[1] = { nx * number + padding, ny * number + SizeOfPart + padding };
	p[2] = { nx * number + SizeOfPart + padding, ny * number + SizeOfPart + padding };
	p[3] = { nx * number + SizeOfPart + padding, ny * number + padding };

	Polygon(dc, p, size);
}

int main(void) {
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	int SizeOfPart = 5;
	int padding = 1;
	int number = 0;

	HDC dc = GetDC(NULL);
	HWND hWnd = GetDesktopWindow();


	HDC dcCompatible = CreateCompatibleDC(dc);
	HBITMAP hbm = CreateCompatibleBitmap(dc, width, height);

	SelectObject(dcCompatible, hbm);

	for (size_t y = 0; y < height / (SizeOfPart + padding); y++) {
		for (size_t x = 0; x < width / (SizeOfPart + padding); x++) {
			number++;
			CreatRect(dcCompatible, x, y, SizeOfPart, width, height, padding, number, hbm);
		}
	}

	for (int i = 0; i < 1000; i++) {
		BitBlt(dc, 0, 0, width, height, dcCompatible, 0, 0, SRCCOPY); Sleep(10);
	}

	return 0;
}
