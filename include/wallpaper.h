#ifndef WALLPAPER_H_
#define WALLPAPER_H_

#include <SDL2/SDL.h>
#include <windows.h>

SDL_Window *create_wallpaper_window(const char *name);

static HWND get_sdl_window_handle(SDL_Window *window);

#endif // WALLPAPER_H_
