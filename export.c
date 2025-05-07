#include "minishell.h"

int valid_identifier(char *str)
{
	int i;

	if (!str || !*str)
		return (0);
	if (!is_alpha(*str) && *str != '_')
		return(0);
	i = 1;
	while (str[i])
	{
		if (!is_alphanumeric(str[i]) && str[i] != '_')
			return (0);
			i++;
	}
		return (1);
}


int process_export(char *arg, t_env **env_list)
{
	char *equal_sign;
	char *name;
	char *value;
	int append;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign == arg)
	{
			write(1, "ooo\n", 4);
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			return(1);
	}
	if (equal_sign > arg + 1 && *(equal_sign - 1) == '+')
	{
			append = 1;
			name = ft_substr(arg, 0, equal_sign - arg - 1);
	}
	else
		name = ft_substr(arg, 0, equal_sign - arg);
	// printf("apped = %d\n", append);
	if (!name || !valid_identifier(name))
	{
		printf("Name: `%s`\n", name);
		printf("Valid identifier check: %d\n", valid_identifier(name));
		if (name)
			free(name);
		write(1, "aaa\n", 4);
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return(1);
	}
	value = ft_strdup(equal_sign + 1);
	if (append)
		env_append(name, value, env_list);
	else
		update_env(name, value, env_list);
	free(name);
	free(value);
	return (0);
}
int ft_export(char **cmd, t_env **env_list)
{
    char *equal_sign;
		int status = 0;
    int i = 1;
     
    if (!cmd || !cmd[i]) 
        return(1);
		while (cmd[i])
		{
				equal_sign = ft_strchr(cmd[i], '=');
				if (equal_sign)
				{
					if (process_export(cmd[i], env_list) != 0)
						status = 1;
				}
				i++;
		}
    return (status);
}
