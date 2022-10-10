#ifndef __HELPER_H
#define __HELPER_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/limits.h>

char* get_home_dir();
void trim_spaces(char * s);
char* trim(char* str, char c);

#endif
