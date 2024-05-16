/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:41:22 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/16 11:45:49 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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