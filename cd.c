#include "minishell.h"

int ft_cd(char **cmd, t_env *envlist)
{
    char cwd[10240];
    char *oldpwd;
    char *path = NULL;

    if (!getcwd(cwd, sizeof(cwd)))
        return (1);
    oldpwd = ft_strdup(cwd);
    if (!cmd[1] || strcmp(cmd[1], "~") == 0)
    {
        path = getenv("HOME");
        if (!path)
            return (printf("minishell: cd: HOME not set\n"), free(oldpwd), 1);
    }
    else if (cmd[1][0] == '$')
    {
        path = get_env_value(cmd[1] + 1, envlist);
        if (!path)
            return (printf("minishell: cd: %s: undefined variable\n", cmd[1]), free(oldpwd), 1);
    }
    else
        path = cmd[1];
    if (chdir(path) != 0)
        return (printf("minishell: cd: %s: %s\n", path, strerror(errno)), free(oldpwd), 1);
    if (getcwd(cwd, sizeof(cwd)))
    {
        update_env("OLDPWD", oldpwd, &envlist);
        update_env("PWD", cwd, &envlist);
    }
    free(oldpwd);
    return (0);
}
