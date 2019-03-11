#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
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

void SetColorOfPixel(sf::Uint8* pixels, int currArrPos, int currBit)
{
	if (!currBit)
	{
		pixels[currArrPos] = 100;
		pixels[currArrPos+1] = 100;
		pixels[currArrPos+2] = 100;
		pixels[currArrPos+3] = 100;
		return;
	}
	if (currArrPos < (32 * 240) && currArrPos >= (0))
	{
		pixels[currArrPos] = 255;
		pixels[currArrPos+1] = 255;
		pixels[currArrPos+2] = 255;
		pixels[currArrPos+3] = 0;
	}
	else if (currArrPos < (64 * 240) && currArrPos >= (32 * 240))
	{
		pixels[currArrPos] = 255;
		pixels[currArrPos+1] = 0;
		pixels[currArrPos+2] = 0;
		pixels[currArrPos+3] = 0;
	}
	else if (currArrPos < (184 * 240) && currArrPos >= (64 * 240))
	{
		pixels[currArrPos] = 255;
		pixels[currArrPos+1] = 255;
		pixels[currArrPos+2] = 255;
		pixels[currArrPos+3] = 0;
	}
	else if (currArrPos < (240 * 240) && currArrPos >= (184 * 240))
	{
		pixels[currArrPos] = 0;
		pixels[currArrPos+1] = 128;
		pixels[currArrPos+2] = 0;
		pixels[currArrPos+3] = 0;
	}
	else if (currArrPos >= (240 * 240))
	{
		pixels[currArrPos] = 255;
		pixels[currArrPos+1] = 255;
		pixels[currArrPos+2] = 255;
		pixels[currArrPos+3] = 0;
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
	
    sf::RenderWindow window(sf::VideoMode(W, H, 32), "Space Invaders");
    sf::Uint8        *pixels  = new sf::Uint8[W * H * 4];

	while (window.isOpen())
    {
		Execute8080Op(gameState);
		int currArrPos = 0;
		for(int i = 0x2400; i < 0x3fff; ++i)
		{
			int currByte = gameState->memory[i];
			for (int j = 0; j < 8; j++)
			{
				unsigned char currBit = (currByte >> j) & 1;
				SetColorOfPixel(pixels, currArrPos, currBit);
				currArrPos += 4;
			}
		}
		sf::Texture texture;
		texture.create(W, H); 
		sf::Sprite sprite(texture); // needed to draw the texture on screen
		texture.create(W, H); 
		texture.update(pixels);
		window.clear();
		window.draw(sprite);
		window.display();
		sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
	}

    delete [] pixels;
    return 0;
}