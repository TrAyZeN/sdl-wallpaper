#include <stdlib.h>
#include <string.h>
#include "error.h"

static char *last_error = NULL;

void set_last_error(char *error)
{
	last_error = (char *) malloc(strlen(error) + 1);
	strcpy(last_error, error);
}

char *get_last_error()
{
	if (last_error == NULL)
		return "";

	return last_error;
}
