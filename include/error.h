#ifndef ERROR_H_
#define ERROR_H_

static char *last_error;

char *get_last_error();
void set_last_error(char *error);
void set_last_errorf();

#endif // ERROR_H_
