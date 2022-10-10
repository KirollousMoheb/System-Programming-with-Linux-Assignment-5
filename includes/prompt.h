#ifndef __PROMPT_H
#define __PROMPT_H

#define KCYN "\x1B[36m"
#define RESET "\x1B[0m"
#define GREEN_BOLD "\e[1;32m"
#define BUFFER_SIZE 50

void init_prompt();
void printHistory() ;


#endif
