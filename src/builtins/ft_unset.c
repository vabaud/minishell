#include "../../include/minishell.h"

void	remove_env(t_all *all, char *s)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;

	k = 0;
	i = 0;
	j = 0;
	while (all->env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	while (all->env[i])
	{
		j = 0;
		while (all->env[i][j] != '=')
			j++;
		if (ft_strncmp(all->env[i], s, j))
			new_env[k++] = ft_strdup(all->env[i]);
		i++;
	}
	new_env[k] = NULL;
    free_env(all->env);
	all->env = new_env;
}

void	ft_unset(t_all *all, char **args)
{
	int	i;

	if (!args || !args[0])
	{
		ft_putstr_fd("unset: pas assez d'arguments\n", STDOUT_FILENO);
		return ;
	}
	i = 1;
	while (args[i])
	{
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		remove_env(all, args[i]); // appeler rm_env pour chaque args
		i++;
	}
}
