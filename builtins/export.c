/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:28:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/06 16:35:40 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//does not export to the actual environment inherited from the parent process
//could add the the variable to before the '_' variable
//what is a variable already exists and I try creating one with that name?
//check correct syntax e.g. HELLO=hello
char	**export(char **args, char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(args[1]);
	return (new_envp);
}

//kind of working
char	**unset(char **args, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], args[1], ft_strlen(args[1])))
			break ;
		i++;
	}
	while (envp[i])
	{
		free(envp[i]);
		if (envp[i + 1])
			envp[i] = ft_strdup(envp[i + 1]);
		i++;
	}
	return (envp);
}


