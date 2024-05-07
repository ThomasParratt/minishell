/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:28:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/07 13:09:25 by tparratt         ###   ########.fr       */
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

//does not export to the actual environment inherited from the parent process
//what if a variable already exists and I try creating one with that name?
//check correct syntax e.g. HELLO=hello
char	**export(char **args, char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = malloc_envp(envp);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "_=", 2))
		{
			new_envp[i + 1] = envp[i];
			new_envp[i] = ft_strdup(args[1]);
		}
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_envp);
}

char	**unset(char **args, char **envp)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc_envp(envp);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], args[1], ft_strlen(args[1])))
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


