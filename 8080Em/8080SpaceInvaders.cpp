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
	}
	else if (currArrPos < (32 * 240) && currArrPos >= (0))
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
	
    sf::RenderWindow window(sf::VideoMode(W, H), "Space Invaders");
    sf::Uint8        *pixels  = new sf::Uint8[W * H]; 
	window.clear();
	window.setFramerateLimit(60);
	sf::VertexArray pointmap(sf::Points, 256 * 240);

	while (window.isOpen())
    {
		Execute8080Op(gameState);
		int currArrPos = 0;
		for(register int i = 0x2400; i < 0x3fff; ++i)
		{
			unsigned char currByte = gameState->memory[i];
			for (register int j = 0; j < 8; j++)
			{
				unsigned char currBit = (currByte >> j) & 1;
				int a = i + j - 0x2400;
				pointmap[a].position = sf::Vector2f(a % 256,a / 256);
				pointmap[a].color = currBit ? sf::Color::White : sf::Color::Black;
				if (currBit)
				printf("%d\n", a);
				//SetColorOfPixel(pixels, currArrPos, currBit);
				//currArrPos ++;
			}
		}
		// sf::Texture texture;
		// sf::Sprite sprite(texture); // needed to draw the texture on screen
		// texture.create(W, H);
		// texture.update(pixels);
		// window.clear();
		// window.draw(sprite);
		// window.display();
		sf::Event event;
		window.clear();
		window.draw(pointmap);
		window.display();
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