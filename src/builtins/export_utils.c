#include "../../include/minishell.h"

void print_var(char *env, char **env_tab)
{
    char *value;
    char *new_env;
    int i;

    i = -1;
    new_env = NULL;
    value = NULL;

    while(env[++i] != '=')
        new_env = ft_strcharadd(new_env, env[i]);
    value = env_value(new_env, env_tab);
    ft_printf("declare -x %s=\"%s\"\n", new_env, value);
    free(new_env);
    free(value);
}
