#include <windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "DX9Window.h"

using namespace std;

int main() {
	MSG Message;
	int MaxIterations = 64;
	vector<int> Dimensions = { 640, 480 };
	vector<int> Position = { 0, 0 };
	unsigned long long Zoom = 1.0;
	vector<long double> Offset = { 0.0, 0.0 };  
	vector<int> MandelPosition = { 0, 0 }; 
	vector<int> MandelSize = { Dimensions.at(0), Dimensions.at(1) };

	DX9_Window DXWindow((HINSTANCE)GetWindowLong(GetConsoleWindow(), GWL_HINSTANCE), SW_SHOW, &Position.front(), &Dimensions.front());

	while (true) {
		system("cls");

		std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << "Zoom : " << Zoom << std::endl;
		std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << "Offset.at(0) : " << Offset.at(0) << std::endl;
		std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << "Offset.at(1) : " << Offset.at(1) << std::endl;
		std::cout << "MaxIterations : " << MaxIterations << std::endl;


		if (GetAsyncKeyState(VK_SUBTRACT) &1 ) { Zoom *= 0.5; }
		if (GetAsyncKeyState(VK_ADD) & 1) { Zoom /= 0.5; }

		if (GetAsyncKeyState(VK_LEFT)) { Offset.at(0) -= 0.1 / Zoom;}
		if (GetAsyncKeyState(VK_RIGHT)) { Offset.at(0) += 0.1 / Zoom; }
		if (GetAsyncKeyState(VK_UP)) { Offset.at(1) -= 0.1 / Zoom; }
		if (GetAsyncKeyState(VK_DOWN)) { Offset.at(1) += 0.1 / Zoom; }

		if (GetAsyncKeyState(VK_NEXT)) { MaxIterations /= 1.1; }
		if (GetAsyncKeyState(VK_PRIOR)) { MaxIterations *= 1.1; }

		if (PeekMessage(&Message, NULL, NULL, NULL, PM_REMOVE)) {
			if (Message.message == WM_QUIT) {
				break;
			}
		
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		
		DXWindow.BeginScene();	
		DXWindow.FillRect(&Position.front(), &Dimensions.front(), D3DCOLOR_ARGB(255, 255, 255, 255));
		DXWindow.DrawMandelBrot(&MandelPosition.front(), &MandelSize.front(), Zoom, &Offset.front(), MaxIterations);
		DXWindow.DrawX(std::vector<int>{MandelSize.at(0) / 2, MandelSize.at(1) / 2}, 15, D3DCOLOR_ARGB(32, 255, 255, 255));
		DXWindow.EndScene();
	}

	return 0;
}