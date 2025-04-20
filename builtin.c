/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:09:19 by taya              #+#    #+#             */
/*   Updated: 2025/04/20 22:49:34 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_echo(t_token *token_list, t_env *env_list)
// {
//     int new_line;
//     char *str;
//     int i;
//     int offset;
//     t_token *token =token_list;

//     new_line = 1;
//     token = token->next;
    // while (token && ft_strncmp(token->value, "-n", 2) == 0)
    // {
    //     new_line = 0;
    //     token = token->next;
    // }
//     while (token)
//     {
//         str = token->value;
//         i = 0;
//         while (str[i])
//         {
//             if (str[i] == '$')
//             {
//                 offset = handle_variable(&str[i], env_list);
//                 i += offset + 1; 
//             }
//             else
//             {
//                 printf("%c", str[i]);
//                 i++;
//             }
//         }
//         if (token->has_space == 1)
//             printf(" ");
//         token = token->next;
//     }
//     if (new_line)
//         printf("\n");
//     return (0);
// }
int ft_echo(char **cmd, t_env *env_list)
{
    int i = 1;
    int newline = 1;
    int j;
    int offset;

    while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
    {
        newline = 0;
        i++;
    }
    while (cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (cmd[i][j] == '$')
            {
                offset = handle_variable(&cmd[i][j], env_list);
                j += offset + 1; 
            }
            else
            {
                printf("%c", cmd[i][j]);
                j++;
            }
        }
        // printf("%s", cmd[i]);
        if (cmd[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}

// int ft_export(t_token *token, t_env **env_list)
// {
//     t_token *input = token;
//    char *equal_sign;
//    char *name;
//    char *value;
   
//    input = input->next;
//    if (!input || !input->value)
//     return(1);
//    equal_sign = ft_strchr(input->value, '=');
//    if (!equal_sign)
//         return(1);
//    name = strndup(input->value, equal_sign - input->value);
//    value = ft_strdup(equal_sign + 1);
//    update_env(name, value, env_list);
//    free(name);
//    free(value);
//    return (0);
// }

int ft_env(t_env *env_list)
{
    t_env *current;
    
    current = env_list;
    while(current)
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
    return(0);
}

int ft_exit(char **cmd, t_env *env_list)
{
    int exit_status;
    t_env *current;
    int i = 1;
    
    current = env_list;
    exit_status = 0;

    if (cmd && cmd[i])
        exit_status = atoi(cmd[i]);
    while (current)
    {
        free(current->name);
        free(current->value);
        free(current);
        current = current->next;
    }
    printf("exit\n");
    exit(exit_status);
    return (0);
}

// int ft_unset(t_token *token, t_env **env_list)
// {
//     t_token *var = token;
//     t_env *current = *env_list;
//     t_env *prev = NULL;

//     var = var->next;
//     if (!var || !var->value)
//         return (1);
//     while(current)
//     {
//         if (strcmp(var->value, current->name) == 0)
//         {
//             if (prev == NULL)
//                 *env_list = current->next;
//             else
//                 prev->next = current->next;
//             free(current->name);
//             free(current->value);
//             free(current);
//             return (0);
//         }
//         prev = current;
//         current = current->next;
//     }
//     return(1);
// }

// int ft_cd(t_token *token)
// {
//     t_token *path = token;
//     char *home_dir;
    
//     if ((path->next && !strcmp(path->next->value, "~")) || !path || !path->next)
//     {
//         home_dir = getenv("HOME");
//         if (!home_dir)
//         {
//             printf("minishell: cd: %s: No such file or directory\n", home_dir);
//             return (1);
//         }
//         if (chdir(home_dir) != 0)
//         {
//             printf("minishell: cd: %s: No such file or directory\n", home_dir);
//             return (1);
//         }
//     }
//     else
//     {
//         path = path->next;
//         if (chdir(path->value) != 0)
//         {
//             printf("minishell: cd: %s: No such file or directory\n", path->value);
//             return (1);
//         }
//     }   
//     return (0);
// }

int ft_pwd()
{
    char cwd[10240];
    if (!getcwd(cwd, sizeof(cwd)))
    {
        printf("error");
        return(1);
    }
    printf("%s\n", cwd);
    return (0);
}

