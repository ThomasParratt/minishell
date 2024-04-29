/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/29 14:47:19 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_paths(char **tokens)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = getenv("PATH");
	if (!path_pointer)
		return (NULL);
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

char	*get_path(char **tokens)
{
	int		i;
	char	*res;
	char	**paths;

	i = 0;
	paths = create_paths(tokens);
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			res = ft_strdup(paths[i]);
			if (!res)
				exit(1);
			free_split(paths);
			return (res);
		}
		i++;
	}
	free_split(paths);
	ft_printf("minishell: %s: command not found\n", tokens[0]);
	return (NULL);
}
