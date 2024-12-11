#include "../../include/minishell.h"

int valid_indentifier(const char *str)
{
    int i;

    if(!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return(0);
    i = 1;
    while(str[i] && str[i] != '=')
    {
        if(!ft_isalnum(str[i]) && str[i] != '_')
            return(0);
        i++;
    }
    return(1);
}


void add_n_up_env(t_all *all, const char *var)
{
    int i;
    int name_len;
    int *name;
    int **new_env;

    name_len = 0;
    while(var[name_len] && var[name_len] != '=')
        name_len++;
    name = ft_substr(var, 0, name_len);
    i = 0;
    while(all->env[i])
    {
        if(ft_strncmp(all->env[i], name, name_len) == 0 && all->env[i][name_len] == '=')
        {
            free(all->env[i]);
            all->env[i] = ft_strdup(var);
            free(name);
            return;
        }
        i++;
    }
    new_env = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while(all->env[i])
    {
        new_env[i] = all->env[i];
        i++;
    }
    new_env[i] = ft_strdup(var);
    new_env[i + 1] = NULL;
    free(all->env);
    all->env = new_env;
    free(name);
}

void ft_export(t_all *all, char **args)
{
    int i;

    if(!args || args[0])
    {
        i = 0;
        while(all->env[i])
        {
            ft_putstr_fd("declarer -x", STDOUT_FILENO);
            ft_putstr_fd(all->env[i], STDOUT_FILENO);
            ft_putchar_fd('\n', STDOUT_FILENO);
        }
        return;
    }
    i = 0;
    while(args[i])
    {
        if(valid_indentifier(args[i]))
            add_n_up_env(all, args[i]);
        else
        {
            ft_putstr_fd("export: n'est pas un indentifier valide :", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
        }
        i++;
    }
}
