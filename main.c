#include "minishell.h"

int pwd()
{
    char path[PATH_MAX];

    if (getcwd(path, PATH_MAX))
    {
        printf("%s\n", path);
        return 1;
    }
    return 0;
}

int main()
{
    char *str;

    while (1)
    {
        str = readline("shell> ");
        if (str[0] == 'p')
            pwd();
        add_history(str);
        printf("%s\n", str);
    }
}
