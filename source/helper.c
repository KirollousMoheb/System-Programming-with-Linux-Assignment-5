#include "../includes/helper.h"

char *get_home_dir()
{
   	// gets the current home directory
   	// dynamically allocates and returns a pointer to a new string, caller must free

    pid_t pid = getpid();
    char *read_path = (char*) malloc(sizeof(char) *1024);
    sprintf(read_path, "/proc/%d/exe", pid);

    char *temp = (char*) malloc(sizeof(char) *1024);
    ssize_t exec_len = readlink(read_path, temp, 1024 - 1);

    if (exec_len < 0)
    {
        free(read_path);
        free(temp);
        return getcwd(NULL, 0);
    }

    temp[exec_len] = '\0';
    for (int i = exec_len - 1; i >= 0; i--)
    {
        if (temp[i] == '/')
        {
            temp[i] = '\0';
            break;
        }
    }

    free(read_path);
    return temp;
}

void trim_spaces(char *s)
{
    char *p = s;
    int l = strlen(p);

    while (isspace(p[l - 1])) p[--l] = 0;
    while (*p && isspace(*p)) ++p, --l;

    memmove(s, p, l + 1);
}

char *trim(char *str, char c)
{
   	// trims occurences of c from front and back
   	// does not modify original pointer, returns new pointer,
   	// but modifies original string. use original pointer to free

    char *t = str;
    while (*t == c)
    {
        t++;
    }

    size_t i = strlen(t) - 1;
    while (t[i] == c)
    {
        t[i] = '\0';
        i--;
    }

    return t;
}
