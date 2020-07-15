#include "workerw.h"

static HWND icon_workerw;

HWND get_wallpaper_workerw()
{
	HWND progman = FindWindow("Progman", NULL);
	icon_workerw = progman;

	// Bring icon and wallpaper workerw to the bottom
	SendMessageTimeout(progman, 0x052C, NULL, NULL,
		SMTO_NORMAL, 1000, NULL);

	if (FindWindowEx(progman, NULL, "SHELLDLL_DefView", NULL) == NULL)
		EnumWindows(find_icon_workerw, NULL);

	// The wallpaper workerw is the workerw behind the icon workerw
	return GetWindow(icon_workerw, GW_HWNDNEXT);
}

static BOOL CALLBACK find_icon_workerw(HWND hwnd, LPARAM lparam)
{
	char *classname = (char *) malloc(10);
	GetClassName(hwnd, classname, 10);

	if (strcmp(classname, "WorkerW") == 0)
	{
		HWND child = FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);
		if (child != NULL)
		{
			icon_workerw = hwnd;
			return FALSE;
		}
	}

	return TRUE;
}
