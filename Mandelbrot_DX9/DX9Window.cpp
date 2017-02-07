#include "DX9Window.h"

//Window Procedure
LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {

	switch (Message) {

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}

					 break;
	}

	return DefWindowProc(Window, Message, WParam, LParam);
}
/*
double MapRange(double OldValue, double OldMin, double OldMax, double NewMin, double NewMax) {

	double NewValue = 0, OldRange = 0, NewRange = 0;

	if (OldMin < 0) {
		if (OldMax >= 0) OldRange = (OldMin*-1) + OldMax;
		if (OldMax < 0) OldRange = (OldMin*-1) - (OldMax*-1);
	}
	if (OldMin >= 0) {
		if (OldMax >= 0) OldRange = OldMax - OldMin;
		if (OldMax < 0) OldRange = OldMin + (OldMax*-1);
	}

	if (NewMin < 0) {
		if (NewMax >= 0) NewRange = NewMax + (NewMin*-1);
		if (NewMax < 0) NewRange = (NewMin*-1) - (NewMax*-1);
	}
	if (NewMin >= 0) {
		if (NewMax >= 0) NewRange = NewMax - NewMin;
		if (NewMax < 0) NewRange = NewMin + (NewMax*-1);
	}

	return NewValue = ((OldValue / OldRange) * NewRange) + NewMin + 1.0f;
}
*/
DX9_Window::DX9_Window(HINSTANCE Instance, int CmdShow, int* Pos, int* Size) {

	ZeroMemory(&this->WindowClass, sizeof(this->WindowClass));

	this->WindowClass.cbSize = sizeof(WNDCLASSEX);
	this->WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	this->WindowClass.lpfnWndProc = WindowProc;
	this->WindowClass.hInstance = Instance;
	this->WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	this->WindowClass.lpszClassName = L"DX9 Window";

	RegisterClassEx(&this->WindowClass);

	this->Window = CreateWindowEx(
		WS_EX_COMPOSITED, // WS_EX_TOPMOST | WS_EX_COMPOSITED | WS_EX_LAYERED | WS_EX_TRANSPARENT WS_EX_CLIENTEDGE
		L"DX9 Window",
		L"Mandelbrot",
		WS_SYSMENU, // WS_CAPTION | WS_SYSMENU
		Pos[0], Pos[1],
		Size[0], Size[1] + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		Instance,
		NULL
	);

	MARGINS DWM_Margins;
	DWM_Margins.cxLeftWidth = -1;
	DWM_Margins.cxRightWidth = -1;
	DWM_Margins.cyBottomHeight = -1;
	DWM_Margins.cyTopHeight = -1;

	DwmExtendFrameIntoClientArea(Window, &DWM_Margins);

	ShowWindow(Window, CmdShow);

	this->D3DInterface = Direct3DCreate9(D3D_SDK_VERSION);

	D3DInterface->EnumAdapterModes(NULL, D3DFMT_A8R8G8B8, NULL, &this->D3DDisplayMode);

	D3DPRESENT_PARAMETERS D3DParameters = { NULL };

	D3DParameters.Windowed = true;
	D3DParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DParameters.hDeviceWindow = this->Window;
	D3DParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	D3DParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	D3DParameters.MultiSampleQuality = NULL;
	D3DParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	D3DParameters.BackBufferWidth = Size[0];
	D3DParameters.BackBufferHeight = Size[1];

	this->D3DInterface->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		this->Window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&D3DParameters,
		&this->D3DDevice
	);

	D3DXCreateLine(D3DDevice, &D3DXLine);
	D3DXLine->SetWidth(1);
	D3DXLine->SetPattern(0xFFFFFFFF);
	D3DXLine->SetAntialias(false);
}


DX9_Window::~DX9_Window(void) {
	UnregisterClass(L"DX9 Window", NULL);
	DestroyWindow(this->Window);
	this->D3DDevice->Release();
	this->D3DInterface->Release();
}

void DX9_Window::BeginScene(void) {
	this->D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, NULL);
	this->D3DDevice->BeginScene();
}

void DX9_Window::EndScene(void) {
	this->D3DDevice->EndScene();
	this->D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void DX9_Window::FillRect(int* Position, int* Size, D3DCOLOR Color) {
	D3DRECT Rect = { Position[0], Position[1], (Position[0] + Size[0]), (Position[1] + Size[1]) };

	this->D3DDevice->Clear(1, &Rect, D3DCLEAR_TARGET, Color, 0.0f, 0);

}

int DX9_Window::CalcMandelBrot(long double OriginReal, long double OriginImaginary, int Max_Iterations) {

	int Count = 0;
	long double Real = OriginReal;
	long double Imaginary = OriginImaginary;
	long double Next;

	while ((pow(Real, (long double)2.0) + pow(Imaginary, (long double)2.0) <= (long double)16.0) && Count <= Max_Iterations) {

		Next = pow(Real, (long double)2.0) - pow(Imaginary, (long double)2.0) + OriginReal;
		Imaginary = (long double)2.0 * Real * Imaginary + OriginImaginary;
		Real = Next;

		if (Real == OriginReal && Imaginary == OriginImaginary && Count >= Max_Iterations) { return -1; }

		Count += 1;
	}

	return Count;

}

long double MapRange(long double OldValue, long double OldMin, long double OldMax, long double NewMin, long double NewMax) {

	long double NewValue = 0.0, OldRange = 0.0, NewRange = 0.0;

	if (OldMin < 0) {
		if (OldMax >= 0) OldRange = (OldMin*-1) + OldMax;
		if (OldMax < 0) OldRange = (OldMin*-1) - (OldMax*-1);
	}
	if (OldMin >= 0) {
		if (OldMax >= 0) OldRange = OldMax - OldMin;
		if (OldMax < 0) OldRange = OldMin + (OldMax*-1);
	}

	if (NewMin < 0) {
		if (NewMax >= 0) NewRange = NewMax + (NewMin*-1);
		if (NewMax < 0) NewRange = (NewMin*-1) - (NewMax*-1);
	}
	if (NewMin >= 0) {
		if (NewMax >= 0) NewRange = NewMax - NewMin;
		if (NewMax < 0) NewRange = NewMin + (NewMax*-1);
	}

	return (long double)NewValue = ((OldValue / OldRange) * NewRange) + NewMin;
}

void DX9_Window::DrawMandelBrot(int* Pos, int* Size, long double Zoom, long double* Offset, int MaxIterations) {
	std::vector<int>CurrentPosition = { Pos[0], Pos[1] };
	std::vector<int>SinglePixel = { 1, 1 };


	for (int x = 0; x < Size[0]; x++) {

		CurrentPosition.at(0) = x + Pos[0];

		for (int y = 0; y < Size[1]; y++) {

			long double RealValue = MapRange(x, 0, Size[0], (long double)(-2.0 / Zoom) + Offset[0], (long double)(2.0 / Zoom) + Offset[0]);
			long double ImaginaryValue = MapRange(y, 0, Size[1], (long double)((-2.0 / ((long double)Size[0] / Size[1])) / Zoom) + Offset[1], (long double)((2.0 / ((long double)Size[0] / Size[1])) / Zoom) + Offset[1]);

			CurrentPosition.at(1) = y + Pos[1];

			int Color = this->CalcMandelBrot(RealValue, ImaginaryValue, MaxIterations);

			this->FillRect(&CurrentPosition.front(), &SinglePixel.front(), this->GenerateColors(Color, MaxIterations));
		}
	}
}

D3DCOLOR DX9_Window::GenerateColors(int Count, int MaxRange) {

	int R = 0, G = 0, B = 0;
	Count = (int)MapRange(Count, -1, MaxRange, -1, 128);

	if (Count == -1) { R = 0; G = 0; B = 0; }
	else if (Count == 0) { R = 255; G = 0; B = 0; }

	else {
		if (Count < 16) {
			R = 16 * (16 - Count);
			G = 0;
			B = 16 * Count - 1;
		}
		else if (Count < 32) {
			R = 0;
			G = 16 * (Count - 16);
			B = 16 * (32 - Count) - 1;
		}
		else if (Count < 64) {
			R = 255 - (Count - 64) * 4;
			G = 0;
			B = 0;
		}
	}

	return D3DCOLOR_ARGB(255, R, G, B);

}

void DX9_Window::DrawX(std::vector<int> Pos, int Size, D3DCOLOR color)
{
	D3DXVECTOR2 points[5];

	D3DXVECTOR2 d3dpoints[2];

	d3dpoints[0] = D3DXVECTOR2(Pos[0] - Size, Pos[1]);
	d3dpoints[1] = D3DXVECTOR2(Pos[0] + Size, Pos[1]);
	this->D3DXLine->Draw(d3dpoints, 2, color);

	d3dpoints[0] = D3DXVECTOR2(Pos[0], Pos[1] - Size);
	d3dpoints[1] = D3DXVECTOR2(Pos[0], Pos[1] + Size);
	this->D3DXLine->Draw(d3dpoints, 2, color);
}