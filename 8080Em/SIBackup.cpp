//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
#include<windows.h>
#include<cstdlib>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<assert.h>
#include<errno.h>
#ifndef EMULATION8080
#define EMULATION8080
#include "8080Emulation.h"
#endif
#ifndef INSTRUCTIONSET8080
#define INSTRUCTIONSET8080
#include "8080InstructionSet.h"
#endif

void SetColorOfPixel(COLORREF* pixels, int currArrPos, int currBit)
{
	if (currBit)
	{
		printf("jalksdfklalskjdfklajsldkfjaskdjlf\n\n\n\n\n\n\n\n\n");
		exit(1);
		pixels[currArrPos] = 255;
		pixels[currArrPos+1] = 255;
		pixels[currArrPos+2] = 255;
		pixels[currArrPos+3] = 255;
	}
	else if (currArrPos < (32 * 240) && currArrPos >= (0))
	{
		pixels[currArrPos] = 0;
		pixels[currArrPos+1] = 0;
		pixels[currArrPos+2] = 0;
		pixels[currArrPos+3] = 255;
	}
	else if (currArrPos < (64 * 240) && currArrPos >= (32 * 240))
	{
		pixels[currArrPos] = 0;
		pixels[currArrPos+1] = 0;
		pixels[currArrPos+2] = 0;
		pixels[currArrPos+3] = 255;
	}
	else if (currArrPos < (184 * 240) && currArrPos >= (64 * 240))
	{
		pixels[currArrPos] = 0;
		pixels[currArrPos+1] = 0;
		pixels[currArrPos+2] = 0;
		pixels[currArrPos+3] = 255;
	}
	else if (currArrPos < (240 * 240) && currArrPos >= (184 * 240))
	{
		pixels[currArrPos] = 0;
		pixels[currArrPos+1] = 0;
		pixels[currArrPos+2] = 0;
		pixels[currArrPos+3] = 255;
	}
	else if (currArrPos >= (240 * 240))
	{
		pixels[currArrPos] = 0;
		pixels[currArrPos+1] = 0;
		pixels[currArrPos+2] = 0;
		pixels[currArrPos+3] = 255;
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	struct State8080* gameState = Initialize8080StateStruct((struct State8080*)calloc(1, sizeof(struct State8080)));
	assert(argc % 2 == 1);
	for (int i = 1; i < argc; i += 2)
	{
		FILE* rom;
		int offset = (int)strtol(argv[i + 1], NULL, 16);
		if (fopen_safe2(&rom, argv[i], "rb") != 0)
		{
			exit(EXIT_FAILURE);
		}
		ReadFileIntoMemory(gameState, rom, offset);
	}
	
	const unsigned int W = 256;
	const unsigned int H = 224;
	
	COLORREF* pixels = (COLORREF*)calloc(512 * 512, sizeof(COLORREF)); // might cause stack overflow

	//https://stackoverflow.com/questions/26005744/how-to-display-pixels-on-screen-directly-from-a-raw-array-of-rgb-values-faster-t
	char szClassName[] = "Space Invaders";
	HINSTANCE hThisInstance = GetModuleHandle(NULL);
	HWND window = CreateWindowEx(WS_EX_STATICEDGE, szClassName, "Bitmap Display Test", WS_CHILD | WS_VISIBLE, 0, 0, 500, 500, HWND_DESKTOP, NULL, hThisInstance, NULL);
	HDC dc = CreateCompatibleDC(GetDC(window)); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);

	while (true)
	{
		Execute8080Op(gameState);
		int currArrPos = 0;
		for (register int i = 0x2400; i < 0x3fff; ++i)
		{
			unsigned char currByte = gameState->memory[i];
			for (register int j = 0; j < 8; j++)
			{
				unsigned char currBit = (currByte >> j) & 1;
				SetColorOfPixel(pixels, currArrPos, currBit);
				currArrPos += 4;
			}
		}

		HBITMAP map = CreateBitmap(W, // width. 512 in my case
			H, // height
			1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
			8 * 4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
			(void*)pixels); // pointer to array

		SelectObject(dc, map); // Inserting picture into our temp HDC
		// Copy image from temp HDC to window
		BitBlt(dc, // Destination
			10,  // x and
			10,  // y - upper-left corner of place, where we'd like to copy
			W, // width of the region
			H, // height
			dc, // source
			0,   // x and
			0,   // y of upper left corner  of part of the source, from where we'd like to copy
			SRCCOPY); // Defined DWORD to juct copy pixels. Watch more on msdn;


		/*for (int j = 0; j < H; j++)
			for (int i = 0; i < W; i++)
				SetPixel(dc, i, j, RGB(pixels[j * W + 3 * i], pixels[j * W + 3 * i + 1], pixels[j * W + 3 * i + 2]));*/
	}
	/*while (window.isOpen())
    {*/
	//	if (gameState->interrupt_enable && time(NULL) - lastInterrupt > 1.0/60.0)
	//	{
	//		printf("jasldfjlkasjdflkaslkdfjkalsdjfklajsdlkf\nasdkjfljadkslf");
	//		PerformInterrupt(gameState, 2);
	//		lastInterrupt = time(NULL);
	//	}
	//	Execute8080Op(gameState);
	//	int currArrPos = 0;
	//	for(register int i = 0x2400; i < 0x3fff; ++i)
	//	{
	//		unsigned char currByte = gameState->memory[i];
	//		for (register int j = 0; j < 8; j++)
	//		{
	//			unsigned char currBit = (currByte >> j) & 1;
	//			SetColorOfPixel(pixels, currArrPos, currBit);
	//			currArrPos+=4;
	//		}
	//	}
	//	sf::Texture texture;
	//	texture.create(W, H);
	//	sf::Sprite sprite(texture); // needed to draw the texture on screen
	//	texture.create(W, H);
	//	texture.update(pixels);
	//	window.clear();
	//	window.draw(sprite);
	//	window.display();
	//	sf::Event event;
 //       while (window.pollEvent(event))
 //       {
 //           // Close window : exit
 //           if (event.type == sf::Event::Closed)
 //               window.close();
 //       }
	//}

    //delete [] pixels;
    return 0;
}