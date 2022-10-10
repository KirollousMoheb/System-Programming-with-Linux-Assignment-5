#include "../includes/export.h"
#include "../includes/local_vars.h"
#include "../includes/helper.h"

extern char *variables[64];
extern char *values[64];

void
export (int argc, char **argv)
{
    for (int i = 1; i <= argc - 1; i++)
    {
        int searched_index = search(variables, argv[i]);
        if (searched_index >= 0)
        {
            setenv(variables[searched_index], values[searched_index], 1);
        }
        else
        {
            printf
                ("Couldn't Export variable %s.The Variable doesn't exist.\n",
                    argv[i]);
            break;
        }
    }
}
