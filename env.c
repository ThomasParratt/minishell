/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:50:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/14 19:40:01 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *str, t_mini *line)
{
	char	*env;
	char	*env_value;
	int		i;

	if (!ft_strncmp(str, "?", 2))
	{
		env_value = ft_strdup(ft_itoa(line->err_num));
		if (!env_value)
			malloc_failure(line);
		return (env_value);
	}
	env = ft_getenv(envp, str);
	if (!env)
		return (NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	env_value = ft_substr(env, i, ft_strlen(env));
	if (!env_value)
		malloc_failure(line);
	return (env_value);
}

char	*ft_getenv(char **envp, char *str)
{
	int		i;
	char	*path_pointer;
	int		len;

	i = 0;
	path_pointer = NULL;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, len) && envp[i][len] == '=')
		{
			path_pointer = ft_strdup(envp[i]);
			if (!path_pointer)
				void_malloc_failure();
			break ;
		}
		i++;
	}
	if (!path_pointer)
		return (NULL);
	return (path_pointer);
}
