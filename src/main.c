#include <SDL2/SDL.h>
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "wallpaper.h"
#include "error.h"

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_EVERYTHING);

	window = create_wallpaper_window("sdl-wallpaper");
	if (window == NULL)
	{
		fprintf(stderr, "An error occured while creating the wallpaper window:\n%s\n", get_last_error());
		goto fail_create_window;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
		goto fail_create_renderer;
	}

	SDL_ShowWindow(window);

	bool running = true;
	int i = 0;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						running = false;
						break;
				}
				break;
			}
		}


		SDL_SetRenderDrawColor(renderer,
			(int) ((sin(i * 0.25) + 1) * 127.5),
			(int) ((sin(i * 0.04) + 1) * 127.5),
			(int) ((sin(i * 0.12) + 1) * 127.5),
			255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		i++;

		SDL_Delay(50);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;

fail_create_renderer:
	SDL_DestroyWindow(window);
fail_create_window:
	SDL_Quit();

	return 1;
}
