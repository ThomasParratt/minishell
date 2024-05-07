/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/07 14:02:47 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getenv(char **envp, char *str)
{
	int		i;
	char	*path_pointer;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			path_pointer = envp[i];
		i++;
	}
	return (path_pointer);
}

static char	**create_paths(char **tokens, char **envp)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = ft_getenv(envp, "PATH");
	if (!path_pointer)
	{
		ft_printf("minishell: %s: No such file or directory\n", tokens[0]);
		return (NULL);
	}
	paths = ft_split(path_pointer, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = join_and_free(paths[i], "/");
		paths[i] = join_and_free(paths[i], tokens[0]);
		i++;
	}
	return (paths);
}

char	*get_path(char **tokens, char **envp)
{
	int		i;
	char	*res;
	char	**paths;

	i = 0;
	paths = create_paths(tokens, envp);
	if (!paths)
	{
		ft_printf("minishell: %s: No such file or directory\n", tokens[0]);
		return (NULL);
	}
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			res = ft_strdup(paths[i]);
			if (!res)
				exit(1);
			free_2d(paths);
			return (res);
		}
		i++;
	}
	free_2d(paths);
	ft_printf("minishell: %s: command not found\n", tokens[0]);
	return (NULL);
}
