#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"
#include "workerw.h"
#include "wallpaper.h"

SDL_Window *create_wallpaper_window(const char *name)
{
	static SDL_Window *window;
	HWND window_handle, workerw;
	char *error_buffer;

	error_buffer = (char *) malloc(256 * sizeof(char));
	if (error_buffer == NULL)
	{
		set_last_error("Failed to allocate error buffer");
		return NULL;
	}

	window = SDL_CreateWindow(name, 0, 0, 0, 0,
		SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
	if (window == NULL)
	{
		sprintf(error_buffer, "Failed to create window: %s", SDL_GetError());
		goto error;
	}

	window_handle = get_sdl_window_handle(window);
	if (window_handle == NULL)
	{
		sprintf(error_buffer, "Failed to get window information: %s", SDL_GetError());
		goto error;
	}

	workerw = get_wallpaper_workerw();
	if (workerw == NULL)
	{
		error_buffer = "Failed to get wallpaper workerw";
		goto error;
	}

	if (SetParent(window_handle, workerw) == NULL)
	{
		sprintf(error_buffer, "Failed to set window parent parent: %s", SDL_GetError());
		goto error;
	}

	if (!SetWindowLongPtr(window_handle,
		GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOACTIVATE))
	{
		sprintf(error_buffer, "Failed to set extended window style: %s", GetLastError());
		goto error;
	}

	if (!SetWindowLongPtr(window_handle, GWL_STYLE, WS_CHILDWINDOW | WS_VISIBLE))
	{
		sprintf(error_buffer, "Failed to set window style: %s", GetLastError());
		goto error;
	}

	BOOL ret = SetWindowPos(window_handle,
		NULL,
		GetSystemMetrics(SM_XVIRTUALSCREEN),
		GetSystemMetrics(SM_YVIRTUALSCREEN),
		GetSystemMetrics(SM_CXVIRTUALSCREEN),
		GetSystemMetrics(SM_CYVIRTUALSCREEN),
		SWP_NOZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
	if (ret == FALSE)
	{
		sprintf(error_buffer, "Failed to set window postion: %s", GetLastError());
		goto error;
	}

	free(error_buffer);
	return window;

error:
	set_last_error(error_buffer);
	free(error_buffer);
	return NULL;
}

static HWND get_sdl_window_handle(SDL_Window *window)
{
	SDL_SysWMinfo info;

	SDL_VERSION(&info.version);
	if (!SDL_GetWindowWMInfo(window, &info))
	{
		return NULL;
	}

	return info.info.win.window;
}
