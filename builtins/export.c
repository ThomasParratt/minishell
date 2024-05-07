/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:28:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/07 15:36:10 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**malloc_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	return (new_envp);
}

static char	*env_exists(char *arg, char **envp)
{
	int		len;
	int		i;
	int		j;
	char	*new_arg;

	len = 0;
	while (arg[len] != '=')
		len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], arg, len))
		{
			new_arg = malloc(sizeof(char) * len + 1);
			j = 0;
			while (envp[i][j] != '=')
			{
				new_arg[j] = envp[i][j];
				j++;
			}
			new_arg[j] = '\0';
			return (new_arg);
		}
		i++;
	}
	return (NULL);
}

//check correct syntax e.g. HELLO=hello
char	**export(char *arg, char **envp)
{
	char	**new_envp;
	int		i;
	char	*new_arg;

	new_envp = malloc_envp(envp);
	new_arg = env_exists(arg, envp);
	if (new_arg)
		envp = unset(new_arg, envp);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "_=", 2))
		{
			new_envp[i + 1] = envp[i];
			new_envp[i] = ft_strdup(arg);
		}
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

char	**unset(char *arg, char **envp)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc_envp(envp);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], arg, ft_strlen(arg)))
			new_envp[j] = ft_strdup(envp[i + 1]);
		else
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}


