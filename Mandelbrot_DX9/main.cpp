#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "DX9Window.h"

using namespace std;

int main() {
	SetConsoleTitle(L"DX9 Mandelbrot Renderer by Instagibz");
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	MSG Message;
	int MaxIterations = 64;
	vector<int> Dimensions = { 640, 480 };
	vector<int> Position = { 0, 0 };
	unsigned long long Zoom = 1;
	vector<long double> Offset = { 0.0, 0.0 };
	vector<int> MandelPosition = { 0, 0 };
	vector<int> MandelSize = { Dimensions.at(0), Dimensions.at(1) };

	DX9_Window DXWindow((HINSTANCE)GetWindowLongPtr(GetConsoleWindow(), GWLP_HINSTANCE), SW_SHOW, Position, Dimensions);

	while (!GetAsyncKeyState(VK_END)) {

		DXWindow.BeginScene();
		DXWindow.Render(MandelPosition, MandelSize, Zoom, Offset, MaxIterations);
		DXWindow.EndScene();

		if (GetAsyncKeyState(VK_SUBTRACT)) { Zoom /= 2; }
		if (GetAsyncKeyState(VK_ADD)) { Zoom *= 2; }

		if (GetAsyncKeyState(VK_LEFT)) { Offset.at(0) -= 0.1 / Zoom; }
		if (GetAsyncKeyState(VK_RIGHT)) { Offset.at(0) += 0.1 / Zoom; }
		if (GetAsyncKeyState(VK_UP)) { Offset.at(1) -= 0.1 / Zoom; }
		if (GetAsyncKeyState(VK_DOWN)) { Offset.at(1) += 0.1 / Zoom; }

		if (GetAsyncKeyState(VK_NEXT)) { MaxIterations /= 1.1; }
		if (GetAsyncKeyState(VK_PRIOR)) { MaxIterations *= 1.1; }

		if (PeekMessage(&Message, NULL, NULL, NULL, PM_REMOVE)) {

			if (Message.message == WM_QUIT) { break; }

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		/*
		system("cls");
		std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << "Zoom : " << Zoom << std::endl;
		std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << "Offset.at(0) : " << Offset.at(0) << std::endl;
		std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << "Offset.at(1) : " << Offset.at(1) << std::endl;
		std::cout << "MaxIterations : " << MaxIterations << std::endl;
		*/
	}

	return 0;
}