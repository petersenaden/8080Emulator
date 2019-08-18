////#include <SFML/Graphics.hpp>
////#include <SFML/Window.hpp>
//#include<windows.h>
//#include<cstdlib>
//#include<stdlib.h>
//#include<stdint.h>
//#include<stdio.h>
//#include<assert.h>
//#include<errno.h>
//#ifndef EMULATION8080
//#define EMULATION8080
//#include "8080Emulation.h"
//#endif
//#ifndef INSTRUCTIONSET8080
//#define INSTRUCTIONSET8080
//#include "8080InstructionSet.h"
//#endif
//
//void SetColorOfPixel(COLORREF* pixels, int currArrPos, int currBit)
//{
//	if (currBit)
//	{
//		printf("jalksdfklalskjdfklajsldkfjaskdjlf\n\n\n\n\n\n\n\n\n");
//		exit(1);
//		pixels[currArrPos] = 255;
//		pixels[currArrPos+1] = 255;
//		pixels[currArrPos+2] = 255;
//		pixels[currArrPos+3] = 255;
//	}
//	else if (currArrPos < (32 * 240) && currArrPos >= (0))
//	{
//		pixels[currArrPos] = 0;
//		pixels[currArrPos+1] = 0;
//		pixels[currArrPos+2] = 0;
//		pixels[currArrPos+3] = 255;
//	}
//	else if (currArrPos < (64 * 240) && currArrPos >= (32 * 240))
//	{
//		pixels[currArrPos] = 0;
//		pixels[currArrPos+1] = 0;
//		pixels[currArrPos+2] = 0;
//		pixels[currArrPos+3] = 255;
//	}
//	else if (currArrPos < (184 * 240) && currArrPos >= (64 * 240))
//	{
//		pixels[currArrPos] = 0;
//		pixels[currArrPos+1] = 0;
//		pixels[currArrPos+2] = 0;
//		pixels[currArrPos+3] = 255;
//	}
//	else if (currArrPos < (240 * 240) && currArrPos >= (184 * 240))
//	{
//		pixels[currArrPos] = 0;
//		pixels[currArrPos+1] = 0;
//		pixels[currArrPos+2] = 0;
//		pixels[currArrPos+3] = 255;
//	}
//	else if (currArrPos >= (240 * 240))
//	{
//		pixels[currArrPos] = 0;
//		pixels[currArrPos+1] = 0;
//		pixels[currArrPos+2] = 0;
//		pixels[currArrPos+3] = 255;
//	}
//}
//
//int main(int argc, char *argv[])
//{
//	(void)argc;
//	struct State8080* gameState = Initialize8080StateStruct((struct State8080*)calloc(1, sizeof(struct State8080)));
//	assert(argc % 2 == 1);
//	for (int i = 1; i < argc; i += 2)
//	{
//		FILE* rom;
//		int offset = (int)strtol(argv[i + 1], NULL, 16);
//		if (fopen_safe2(&rom, argv[i], "rb") != 0)
//		{
//			exit(EXIT_FAILURE);
//		}
//		ReadFileIntoMemory(gameState, rom, offset);
//	}
//	
//	const unsigned int W = 256;
//	const unsigned int H = 224;
//	
//	COLORREF* pixels = (COLORREF*)calloc(512 * 512, sizeof(COLORREF)); // might cause stack overflow
//
//	//https://stackoverflow.com/questions/26005744/how-to-display-pixels-on-screen-directly-from-a-raw-array-of-rgb-values-faster-t
//	char szClassName[] = "Space Invaders";
//	HINSTANCE hThisInstance = GetModuleHandle(NULL);
//	HWND window = CreateWindowEx(WS_EX_STATICEDGE, szClassName, "Bitmap Display Test", WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, HWND_DESKTOP, NULL, hThisInstance, NULL);
//	HDC dc = CreateCompatibleDC(GetDC(window)); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
//
//	while (true)
//	{
//		Execute8080Op(gameState);
//		int currArrPos = 0;
//		for (register int i = 0x2400; i < 0x3fff; ++i)
//		{
//			unsigned char currByte = gameState->memory[i];
//			for (register int j = 0; j < 8; j++)
//			{
//				unsigned char currBit = (currByte >> j) & 1;
//				SetColorOfPixel(pixels, currArrPos, currBit);
//				currArrPos += 4;
//			}
//		}
//
//		HBITMAP map = CreateBitmap(W, // width. 512 in my case
//			H, // height
//			1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
//			8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
//			(void*)pixels); // pointer to array
//
//		SelectObject(dc, map); // Inserting picture into our temp HDC
//		// Copy image from temp HDC to window
//		BitBlt(dc, // Destination
//			10,  // x and
//			10,  // y - upper-left corner of place, where we'd like to copy
//			W, // width of the region
//			H, // height
//			dc, // source
//			0,   // x and
//			0,   // y of upper left corner  of part of the source, from where we'd like to copy
//			SRCCOPY); // Defined DWORD to juct copy pixels. Watch more on msdn;
//
//
//		/*for (int j = 0; j < H; j++)
//			for (int i = 0; i < W; i++)
//				SetPixel(dc, i, j, RGB(pixels[j * W + 3 * i], pixels[j * W + 3 * i + 1], pixels[j * W + 3 * i + 2]));*/
//	}
//	/*while (window.isOpen())
//    {*/
//	//	if (gameState->interrupt_enable && time(NULL) - lastInterrupt > 1.0/60.0)
//	//	{
//	//		printf("jasldfjlkasjdflkaslkdfjkalsdjfklajsdlkf\nasdkjfljadkslf");
//	//		PerformInterrupt(gameState, 2);
//	//		lastInterrupt = time(NULL);
//	//	}
//	//	Execute8080Op(gameState);
//	//	int currArrPos = 0;
//	//	for(register int i = 0x2400; i < 0x3fff; ++i)
//	//	{
//	//		unsigned char currByte = gameState->memory[i];
//	//		for (register int j = 0; j < 8; j++)
//	//		{
//	//			unsigned char currBit = (currByte >> j) & 1;
//	//			SetColorOfPixel(pixels, currArrPos, currBit);
//	//			currArrPos+=4;
//	//		}
//	//	}
//	//	sf::Texture texture;
//	//	texture.create(W, H);
//	//	sf::Sprite sprite(texture); // needed to draw the texture on screen
//	//	texture.create(W, H);
//	//	texture.update(pixels);
//	//	window.clear();
//	//	window.draw(sprite);
//	//	window.display();
//	//	sf::Event event;
// //       while (window.pollEvent(event))
// //       {
// //           // Close window : exit
// //           if (event.type == sf::Event::Closed)
// //               window.close();
// //       }
//	//}
//
//    //delete [] pixels;
//    return 0;
//}

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

//prototypes
DWORD SetColorOfPixel(int currArrPos, unsigned char currBit);
void fillGrid();
LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam);
void CALLBACK timerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

#define ORG_WIDTH           224
#define ORG_HEIGHT          256
#define WINDOW_CLASS_NAME   "Space Invaders Emulator"

#define WIN_WIDTH           448
#define WIN_HEIGHT          512
#define TIMER_INTERVAL      17

/* Globals */
HINSTANCE       g_hInst = 0;
HWND            g_hWnd = 0;
HBITMAP         g_hBmp = 0;
HBITMAP         g_hBmpOld = 0;
HDC             g_hMemDC = 0;
UINT32* g_pPixels = 0;
BYTE            g_Screen[ORG_WIDTH * ORG_HEIGHT];
BOOL            isPaused;
HWND            hwnd;
MMRESULT        timerEvent;
const char		szClassName[] = "SpaceInvadersWindowClass";
static struct State8080* gameState;
static const int MAIN_WINDOW_WIDTH = 464;
static const int MAIN_WINDOW_HEIGHT = 570;

int __stdcall WinMain(
	_In_ HINSTANCE		hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_ LPSTR			lpCmdLine,
	_In_ int			nShowCmd
)
{
	// lesson learned - always srand first time in main and only once
	srand((unsigned int)GetTickCount64());

	//SI-specific stuff
	int argc = 8;
	const char* argv[] = { "./SI_ROM/invaders_h.rom", "0x0", "./SI_ROM/invaders_g.rom", "0x800", "./SI_ROM/invaders_f.rom", "0x1000", "./SI_ROM/invaders_e.rom", "0x1800" };

	gameState = Initialize8080StateStruct((struct State8080*)calloc(1, sizeof(struct State8080)));
	//assert(argc % 2 == 1);
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
	bmi.bmiHeader.biWidth = 448;
	bmi.bmiHeader.biHeight = -512;
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

	ShowWindow(g_hWnd, nShowCmd); //must be before showwindow or timercallbakc will 
	//preempt the memory allocation

	ReleaseDC(hwnd, hdc);

	while (GetMessage(&messages, NULL, 0, 0)) {
		TranslateMessage(&messages);
		DispatchMessage(&messages);
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
			timerEvent = timeSetEvent(20, 0, (LPTIMECALLBACK)timerCallback, 0, TIME_PERIODIC);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC deviceContext = BeginPaint(hwnd, &ps);

			BitBlt(deviceContext, 0, 0, WIN_WIDTH, WIN_HEIGHT, g_hMemDC, 0, 0, SRCCOPY);

			EndPaint(hwnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
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

void CALLBACK timerCallback(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	Execute8080Op(gameState);

	fillGrid();
}

void fillGrid()
{
	int currArrPos = 0;
	int currPixelArrPos = 0;
	for (register int i = 0x2400; i < 0x3fff; ++i)
	{
		unsigned char currByte = gameState->memory[i];
		for (register int j = 0; j < 8; j++)
		{
			unsigned char currBit = (currByte >> j) & 1;
			g_pPixels[currPixelArrPos++] = SetColorOfPixel(currArrPos, currBit);
			currArrPos += 4;
		}
	}
	// Convert 256x224 gfx to 448x512 bitmap

	//for (int y = 0; y < WIN_HEIGHT; ++y) {
	//	for (int x = 0; x < WIN_WIDTH; ++x) {
	//		//x1 = x * ORG_WIDTH / WIN_WIDTH;
	//		//y1 = y * ORG_HEIGHT / WIN_HEIGHT;

	//		DWORD dbColor;// =// g_Screen[y1 * ORG_WIDTH + x1];
	//		int randNum = rand() % (4 - 1 + 1) + 1;

	//		if (randNum == 1) {
	//			dbColor = 0xFFFFFFFF;
	//		}
	//		else if (randNum == 2) {
	//			dbColor = 0xFFFF0000;
	//		}
	//		else if (randNum == 3) {
	//			dbColor = 0xFF00FF00;
	//		}
	//		else if (randNum == 4) {
	//			dbColor = 0xFF0000FF;
	//		}
	//		else {
	//			dbColor = 0x00000000;
	//		}

	//		g_pPixels[y * WIN_WIDTH + x] = dbColor;
	//	}
	//}

	InvalidateRect(g_hWnd, 0, false);
}

DWORD SetColorOfPixel(int currArrPos, unsigned char currBit)
{
	DWORD returnVal = 0;
	if (currBit)
	{
		returnVal = 0;
	}

	if (currArrPos < (32 * 240) && currArrPos >= (0))
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
	return returnVal;
}