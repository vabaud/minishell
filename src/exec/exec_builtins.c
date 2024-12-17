#include "../../include/minishell.h"

void exec_builtins(t_all *all, t_command *cmd)
{
    if(!ft_strncmp("cd", cmd->args[0], INT_MAX))
        all->exit_code = ft_cd(cmd->args);
}