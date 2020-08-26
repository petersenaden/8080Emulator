#include<windows.h>
#include<cstdlib>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<assert.h>
#include<errno.h>
#include<mmsystem.h>

#pragma comment(lib, "winmm.lib")

#ifndef EMULATION8080
#define EMULATION8080
#include "8080Emulation.h"
#endif

#ifndef INSTRUCTIONSET8080
#define INSTRUCTIONSET8080
#include "8080InstructionSet.h"
#endif

#define WINDOW_CLASS_NAME   "Space Invaders Emulator"
#define SCREEN_WIDTH           224
#define SCREEN_HEIGHT          256

//prototypes
DWORD SetColorOfPixel(int currArrPos, unsigned char currBit);
void FillGrid();
LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam);

/* Globals */
HINSTANCE       g_hInst = 0;
HWND            g_hWnd = 0;
HBITMAP         g_hBmp = 0;
HBITMAP         g_hBmpOld = 0;
HDC             g_hMemDC = 0;
UINT32*			g_pPixels = 0;
BOOL            isPaused;
HWND            hwnd;
MMRESULT        timerEvent;
const char		szClassName[] = "SpaceInvadersWindowClass";
struct State8080* gameState;
static const int MAIN_WINDOW_WIDTH = 224;
static const int MAIN_WINDOW_HEIGHT = 256;

int __stdcall WinMain(
	_In_ HINSTANCE		hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_ LPSTR			lpCmdLine,
	_In_ int			nShowCmd
)
{
	// lesson learned - always srand first time in main and only once
	srand((unsigned int)GetTickCount64());
	FILE* stream;
	// Redirect logging to output file
	if (freopen_s(&stream, "freopen.txt", "w+", stdout) != 0)
	{
		exit(EXIT_FAILURE);
	}

	//SI-specific stuff
	int argc = 8;
	const char* argv[] = { "./SI_ROM/invaders_h.rom", "0x0", "./SI_ROM/invaders_g.rom", "0x800", "./SI_ROM/invaders_f.rom", "0x1000", "./SI_ROM/invaders_e.rom", "0x1800" };

	gameState = Initialize8080StateStruct((struct State8080*)calloc(1, sizeof(struct State8080)));
	for (int i = 0; i < argc; i += 2)
	{
		FILE* rom;
		int offset = (int)strtol(argv[i + 1], NULL, 16);
		if (fopen_safe2(&rom, argv[i], "rb") != 0)
		{
			exit(EXIT_FAILURE);
		}
		ReadFileIntoMemory(gameState, rom, offset);
	}
	//SI-specific stuff

	MSG messages;
	WNDCLASSEX wincl;

	wincl.hInstance = hInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProc;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = MAKEINTRESOURCE(100); // don't know what this does
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	if (!RegisterClassEx(&wincl)) {
		return EXIT_FAILURE;
	}

	g_hWnd = CreateWindowEx(0, szClassName, WINDOW_CLASS_NAME,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, MAIN_WINDOW_WIDTH,
		MAIN_WINDOW_HEIGHT, HWND_DESKTOP, NULL, hInstance, NULL);
	if (g_hWnd == NULL)
	{
		// log error
		return false;
	}

	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biWidth = 224;
	bmi.bmiHeader.biHeight = 256;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiColors[0].rgbBlue = 0;
	bmi.bmiColors[0].rgbGreen = 0;
	bmi.bmiColors[0].rgbRed = 0;
	bmi.bmiColors[0].rgbReserved = 0;

	HDC hdc = GetDC(hwnd);
	// allocates 0s for the pixel array
	g_hBmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)& g_pPixels, NULL, 0);
	if (g_hBmp == NULL)
	{
		return false;
	}
	g_hMemDC = CreateCompatibleDC(hdc);
	g_hBmpOld = (HBITMAP)SelectObject(g_hMemDC, g_hBmp);

	ShowWindow(g_hWnd, nShowCmd); //must be before showwindow or timercallback will 
	//preempt the memory allocation

	ReleaseDC(hwnd, hdc);
	while (1) {
		if (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) {
			// Without the below condition, the program will continue to run in the background even
			// after the window has been closed. Be mindful of WM_Quit vs WM_Destroy vs WM_Close
			if (messages.message == WM_QUIT)
			{
				return TRUE;
			}
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}
		// Business logic here
		Execute8080Op(gameState);
		FillGrid();
	}

	return 0;
}

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			break;
		}
		case WM_CREATE:
		{
			//wrong - timeSetEvent is deprecated...but still works. I'm not gonna complain
			//timerEvent = timeSetEvent(4, 0, (LPTIMECALLBACK)timerCallback, 0, TIME_PERIODIC);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC deviceContext = BeginPaint(hwnd, &ps);

			BitBlt(deviceContext, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 40002:
			{
				PostQuitMessage(0);
				break;
			}
			}
			break;
		}
		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return 0;
}

void FillGrid()
{
	// Have to rotate CW 90 degrees because that's how
	// memory is laid out.
	int currArrPos = 0;
	int currentColumn = 0;
	int currentCoordinate = 0;
	int currCycle = 0;
	// VRAM starts at 0x2400
	for (register int i = 0x2400; i < 0x3fff; ++i)
	{
		unsigned char currByte = gameState->memory[i];
		for (register int j = 0; j < 8; ++j)
		{
			unsigned char currBit = (currByte >> j) & 1;
			g_pPixels[currentCoordinate] = SetColorOfPixel(currArrPos, currBit);
			currArrPos += 4;
			if (++currCycle == SCREEN_HEIGHT)
			{
				currCycle = 0;
				currentCoordinate = ++currentColumn;
			}
			else
			{
				currentCoordinate += SCREEN_WIDTH;
			}
		}
	}
	InvalidateRect(g_hWnd, 0, false);
}

DWORD SetColorOfPixel(int currArrPos, unsigned char currBit)
{
	DWORD returnVal = 0;
	if (currBit)
	{
		returnVal = 0xFF00FF00;
	}
	else
	{
		returnVal = 0x00000000;
	}
		/*if (currArrPos < (32 * 240) && currArrPos >= (0))
		{
			returnVal = 0xFFFFFFFF;
		}
		else if (currArrPos < (64 * 240) && currArrPos >= (32 * 240))
		{
			returnVal = 0xFF00FF00;
		}
		else if (currArrPos < (184 * 240) && currArrPos >= (64 * 240))
		{
			returnVal = 0x00000000;
		}
		else if (currArrPos < (240 * 240) && currArrPos >= (184 * 240))
		{
			returnVal = 0xFF0000FF;
		}
		else if (currArrPos >= (240 * 240))
		{
			returnVal = 0xFF00FF00;
		}
	}
	else
	{
		returnVal = 0;
	}*/
	return returnVal;
}