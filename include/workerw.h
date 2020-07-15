#ifndef WORKERW_H_
#define WORKERW_H_

#include <windows.h>

static HWND icon_workerw;

HWND get_wallpaper_workerw();

static BOOL CALLBACK find_icon_workerw(HWND hwnd, LPARAM lparam);

#endif // WORKERW_H_
