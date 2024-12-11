#include "../../include/minishell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path_tab;
	char	*full_path;
	char	*cmd_path;

	i = 0;
	full_path = env_value("PATH", env);
	printf("%s\n", full_path);
	if (!full_path)
		return (NULL);
	path_tab = ft_split(full_path, ':');
	free(full_path);
	while (path_tab[i])
	{
		full_path = ft_strjoin(path_tab[i], "/");
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
			return (free_env(path_tab), cmd_path);
		i++;
		free(cmd_path);
	}
	free_env(path_tab);
	return (NULL);
}
