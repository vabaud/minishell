#include <stdio.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]) && (i < n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*s2;

	i = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	s_len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub_str = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	while (len)
	{
		sub_str[i] = s[start];
		start++;
		i++;
		len--;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

char	**env_cpy(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = NULL;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup("?=0");
	return (new_env);
}

char	*ft_strcharadd_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
	{
		printf("ERREUR D'ALLOCATION MEMOIRE\n");
		return (NULL);
	}
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_strcharadd(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_strcharadd_first(c));
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!add)
	{
		printf("ERREUR D'ALLOCATION\n");
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		add[i] = str[i];
		i++;
	}
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

int main(int ac, char **av, char **envp)
{
    char *str;
    str = "test$??ll";
    int start = 0;
    int i = 0;
    int y = 0;
    char **env_tab = env_cpy(envp);
    while(str[i])
    {
        if (str[i] == '$')
            break;
        i++;
    }
    i++;
    start = i++;
    while (ft_isalnum(str[i]))
        i++;
    char *env = ft_substr(str, start, i - start);
    while (env_tab[y])
    {
        int j = 0;
        while (env_tab[y][j] != '=')
            j++;
        if (!ft_strncmp(env, env_tab[y], j))
        {
            printf("%s\n", ft_substr(env_tab[y], ++j, ft_strlen(env_tab[y]) - 1));
        }
        y++;
    }
}
