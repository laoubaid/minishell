/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:42:18 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/29 19:07:06 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

char	*env_fetch(char *var)
{
	while (*var && *var != '=')
		var++;
	if (*var == '=' && *(var + 1))
		return (*var = 0, var + 1);
	return (NULL);
}

t_env	*env_init(char **env)
{
	t_env	*head;
	t_env	*tmp;
    char    *dup;

	tmp = malloc(sizeof(t_env));
    dup =  ft_strdup(*env);
	tmp->name = dup;
	tmp->value = env_fetch(dup);
	head = tmp;
	env++;
	while(*env)
	{
		tmp->next = malloc(sizeof(t_env));
        dup =  ft_strdup(*env);
		tmp->name = dup;
		tmp->value = env_fetch(dup);
		tmp = tmp->next;
		env++;
	}
	tmp->next = NULL;
	return (head);
}

char   **env_default(void)
{
    char **env;

    env = malloc(sizeof(char *) * 4);
    env[0] = getcwd(NULL, 0);
    env[1] = ft_strdup("SHLVL=2");
    env[2] = ft_strdup("_=/usr/bin/bash");     
    env[3] = NULL;
    // int i = 0;
    // while (env[i])
    // {
    //     printf("%s\n", env[i]);
    //     i++;
    // }
    return (env);
}

char	**env_dup(char **env)
{
	char	**new_env;
	int i;
	
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_param *param_init(char **env)
{
	t_param *param;

	param = malloc(sizeof(t_param));
    if (!*env)
        param->env_arr = env_default();
    else
        param->env_arr = env_dup(env);
	param->env = env_init(param->env_arr);
    return (param);
}
