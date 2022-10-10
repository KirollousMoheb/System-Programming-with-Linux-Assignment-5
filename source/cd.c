#include "../includes/cd.h"

bool cd(char *path)
{
    char *final_path;
    if (strcmp(path, "~") == 0)
    {
        final_path = get_home_dir();
    }
    else if (strcmp(path, "") == 0)
    {
        final_path = get_home_dir();
    }
    else
    {
        final_path = path;
    }

    int ret_val = chdir(final_path);
    if (ret_val < 0)
    {
        perror("Could not change directory");
        return false;
    }

    return true;
}

void handle_cd(int argc, char **argv)
{
    if (argc == 1)
    {
        cd("~");
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Could not change directory: Invalid arguments\n");
        return;
    }
    else
    {
        char *temp = trim(argv[1], '\"');
        temp = trim(temp, '\'');
        cd(temp);
    }
}
