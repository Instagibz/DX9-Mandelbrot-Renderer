#pragma once
#include <math.h>
#include <vector>
#include <string>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

class DX9_Window {

public:
	LPDIRECT3D9			D3DInterface;
	LPDIRECT3DDEVICE9	D3DDevice;
	D3DDISPLAYMODE		D3DDisplayMode;

	LPD3DXLINE			D3DXLine;
	LPD3DXFONT			D3DFont;

	HWND				Window;
	WNDCLASSEX			WindowClass;

	DX9_Window::DX9_Window(HINSTANCE Instance, int CmdShow, std::vector<int> Pos, std::vector<int> Size);
	DX9_Window::~DX9_Window(void);

	void DX9_Window::BeginScene(void);
	void DX9_Window::Render(std::vector<int> MandelPosition, std::vector<int> MandelSize, unsigned long long Zoom, std::vector<long double> Offset, int MaxIterations);
	void DX9_Window::EndScene(void);

	void DX9_Window::FillRect(std::vector<int> Position, std::vector<int> Size, D3DCOLOR Color);

	//the mandelbrot function... for more information visit -> https://en.wikipedia.org/wiki/Mandelbrot_set
	int DX9_Window::CalcMandelBrot(long double OriginReal, long double OriginImaginary, int Max_Iterations);
	void DX9_Window::DrawMandelBrot(std::vector<int> Pos, std::vector<int> Size, long double Zoom, std::vector<long double> Offset, int MaxIterations);
	D3DCOLOR DX9_Window::GenerateColors(int Count, int MaxRange);
	void DX9_Window::DrawCrosshair(std::vector<int> Pos, int Size, D3DCOLOR color);
	long double DX9_Window::MapRange(long double OldValue, long double OldMin, long double OldMax, long double NewMin, long double NewMax);
	void DX9_Window::DrawString(std::vector<int> Pos, std::vector<int> Size, std::string Text, D3DCOLOR Color);
};