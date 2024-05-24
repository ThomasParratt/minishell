/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:00:48 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/24 12:13:10 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_failure(void)
{
	ft_putendl_fd("minishell: malloc failure", 2);
	exit(ENOMEM);
}

char	**malloc_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (NULL);
	return (new_envp);
}

char	**envp_dup(char **envp)
{
	char	**res;
	int		i;

	res = malloc_envp(envp);
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
			return(NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	free_2d(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

char	*join_and_free(char *prompt, char *str)
{
	char	*temp;

	temp = ft_strjoin(prompt, str);
	if (!temp)
	{
		free(prompt);
		malloc_failure();
	}
	free(prompt);
	prompt = temp;
	return (prompt);
}
