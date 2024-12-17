#include "../../include/minishell.h"

int valid_indentifier(const char *str)
{
    int i;

    if(!str || !ft_isalpha(str[0]) || str[0] != '_')
        return(0);
    i = 1;
    while(str[i] && str[i] != '=')
    {
        if(!ft_isalnum(str[i]) || str[i] != '_')
            return(0);
        i++;
    }
    return(1);
}


int browse_env(char **env, const char *var, char *name, int name_len)
{
    int i; 

    i = 0;
    while(env[i])
    {
        if(ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
        {
            free(env[i]);
            env[i] = ft_strdup(var);
            free(name);
            return 1;
        }
        i++;
    }   
    return(0);
}

int add_n_up_env(t_all *all, const char *var)
{
    int i;
    int name_len;
    char *name;
    char **new_env;

    i = 0;
    name_len = 0;
    while(var[name_len] && var[name_len] != '=')
        name_len++;
    name = ft_substr(var, 0, name_len);
    if (browse_env(all->env, var, name, name_len))
        return 0;
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
    return 1;
}

int ft_export(t_all *all, char **args)
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
            i++;
        }
        return 0;;
    }
    i = -1;
    while(args[++i])
    {
        if(valid_indentifier(args[i]))
            add_n_up_env(all, args[i]);
        else
        {
            ft_putstr_fd("export: n'est pas un indentifier valide :", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
        }
    }
    return 1;
}
