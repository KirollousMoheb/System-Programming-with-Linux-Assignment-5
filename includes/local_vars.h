#ifndef __LOCALVARIABLES_H
#define __LOCALVARIABLES_H


int search (char **a, char *key);
int check_variable (char *line);
void save_variable (char *line, char **variables, char **values);
void print_variables (char **variables, char **values);

#endif
