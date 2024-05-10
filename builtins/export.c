/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:28:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/10 17:18:02 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*env_exists(char *arg, char **envp)
{
	int		len;
	int		i;
	int		j;
	char	*existing;

	len = 0;
	while (arg[len] != '=')
		len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], arg, len))
		{
			existing = malloc(sizeof(char) * len + 1);
			if (!existing)
				exit(1);
			j = 0;
			while (envp[i][j] != '=')
			{
				existing[j] = envp[i][j];
				j++;
			}
			existing[j] = '\0';
			return (existing);
		}
		i++;
	}
	return (NULL);
}

static char	**unset_existing(char *arg, char **envp)
{
	char		**new_envp;
	char		*existing;

	existing = env_exists(arg, envp);
	if (existing)
	{
		new_envp = unset(existing, envp);
		free(existing);
		return (new_envp);
	}
	return (envp);
}

//check correct syntax e.g. HELLO=hello
char	**export(char *arg, char **envp)
{
	char		**new_envp;
	int			i;

	envp = unset_existing(arg, envp);
	new_envp = malloc_envp(envp);
	if (!new_envp)
		exit(1);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "_=", 2))
		{
			new_envp[i + 1] = ft_strdup(envp[i]);
			new_envp[i] = ft_strdup(arg);
		}
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	free_2d(envp);
	return (new_envp);
}

char	**unset(char *arg, char **envp)
{
	char		**new_envp;
	int			i;
	int			j;

	new_envp = malloc_envp(envp);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, ft_strlen(arg)))
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free_2d(envp);
	return (new_envp);
}


