#pragma once
#include <math.h>
#include <vector>

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

	HWND				Window;
	WNDCLASSEX			WindowClass;

	DX9_Window::DX9_Window(HINSTANCE Instance, int CmdShow, int* Pos, int* Size);
	DX9_Window::~DX9_Window(void);

	void DX9_Window::BeginScene(void);
	void DX9_Window::EndScene(void);

	void DX9_Window::FillRect(int* Position, int* Size, D3DCOLOR Color);

	//the mandelbrot function is pretty simple, for more information visit -> https://en.wikipedia.org/wiki/Mandelbrot_set
	int DX9_Window::CalcMandelBrot(long double OriginReal, long double OriginImaginary, int Max_Iterations);
	void DX9_Window::DrawMandelBrot(int* Pos, int* Size, long double Zoom, long double* Offset, int MaxIterations);
	D3DCOLOR DX9_Window::GenerateColors(int Count, int MaxRange);
	void DX9_Window::DrawX(std::vector<int> Pos, int Size, D3DCOLOR color);
		
};