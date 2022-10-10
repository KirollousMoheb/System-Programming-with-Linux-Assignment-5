#include "../includes/prompt.h"
#include "../includes/helper.h"
extern char history[10][BUFFER_SIZE];

void printHistory() {
    char * host_name = (char * ) malloc(sizeof(char) * (1024 + 1));
    gethostname(host_name, (1024 + 1));
    int i;
    for (i = 0; i < 10; i++) {
        if (!strcmp(history[i], ""))
            continue;
        printf("\n%d)", i + 1);
        printf("%s", history[i]);
    }
    printf("\n");
    printf("%s%s@%s:~%s%s$ %s", GREEN_BOLD, getenv("USER"), host_name, KCYN, getcwd(NULL, 1024),
        RESET);

}


void init_prompt()
{
    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete);
    // Configure up arrow key to print the last 10 commands by calling printHistory onclick
    rl_bind_keyseq("\\e[A", (int( * )(int, int)) printHistory);
   char * host_name = (char * ) malloc(sizeof(char) * (1024 + 1));
   gethostname(host_name, (1024 + 1));

}



