#include "../includes/helper.h"
#include "../includes/redirection.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void redirect_output(char *file_name)
{
    int out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}

void redirect_input(char *file_name)
{
    int in = open(file_name, O_RDONLY);
    dup2(in, 0);
    close(in);
}

int check_redirection(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '>')
        {
            return 1;
        }
        else if (str[i] == '<')
        {
            return 0;
        }
        else if (str[i] == '2' && str[i + 1] == '>')
        {
            return 2;
        }

        i++;
    }

    return -1;

}
