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
