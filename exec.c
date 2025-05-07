#include "minishell.h"



int  is_alphanumeric(int c)
{
    return ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9'));
}
int  is_alpha(int c)
{
    return ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z'));
}

int handle_variable(char *str, t_env *env_list)
{
    int var_len;
    char *var;
    char *value;

    var_len = 0;
    while (str[var_len + 1] && (is_alphanumeric(str[var_len + 1]) || str[var_len + 1] == '_'))
        var_len++;
    if (var_len > 0)
    {
        var = ft_substr(str, 1, var_len);
        value = get_env_value(var, env_list);
        if (value)
            printf("%s", value);
        free(var);
        return (var_len);
    }
    else
    {
        printf("$");
        return (0);
    }
}



int execute_builtin(t_tree *node, t_env **envlist)
{
    if (strcmp(node->cmd[0], "echo") == 0)
        return(ft_echo(node->cmd, *envlist));
    else if (strcmp(node->cmd[0], "cd") == 0)
        return(ft_cd(node->cmd, *envlist));
    else if (strcmp(node->cmd[0], "pwd") == 0)
        return(ft_pwd());
    else if (strcmp(node->cmd[0], "export") == 0)
        return(ft_export(node->cmd, envlist));
    else if (strcmp(node->cmd[0], "unset") == 0)
        return(ft_unset(node->cmd, envlist));
    else if (strcmp(node->cmd[0], "env") == 0)
        return(ft_env(envlist));
    else if (strcmp(node->cmd[0], "exit") == 0)
        return(ft_exit(node->cmd, *envlist));
    return (0);
}


