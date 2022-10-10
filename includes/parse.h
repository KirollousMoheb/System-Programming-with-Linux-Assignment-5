#ifndef __PARSE_H
#define __PARSE_H
#include "helper.h"


int parse (char *line, char **argv);
int parse_redirection(char *line, char **argv);
int check_redirection(char *str);
#endif
