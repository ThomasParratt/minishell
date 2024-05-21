/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/21 12:01:25 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **envp, char *str)
{
	int		i;
	char	*path_pointer;
	char	*res;
	int		j;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			path_pointer = envp[i];
		i++;
	}
	i = 0;
	while (path_pointer[i] != '=')
		i++;
	i++;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(path_pointer) - i + 1));
	if (!res)
		return (NULL);
	while (path_pointer[i])
	{
		res[j] = path_pointer[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
} 

static char	**create_paths(char **tokens, char **envp)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = ft_getenv(envp, "PATH");
	if (!path_pointer)
	{
		ft_printf("minishell: %s: No such file or directory\n", tokens[0]); //this does not print
		return (NULL);
	}
	paths = ft_split(path_pointer, ':');
	if (!paths)
		return (NULL);
	free(path_pointer);
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
