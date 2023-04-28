#ifndef SIMPLE_SHELL_PATHHANDLING_H
#define SIMPLE_SHELL_PATHHANDLING_H
char *findEnv(char *search);
char *myStrDup(char *toDupe);
char *get_location(char *command);
char *my_strcat(char *destination, const char *source);
#endif
