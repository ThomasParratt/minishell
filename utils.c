/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:00:48 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/21 14:37:27 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_message(char **args)
{
	char	*err_str;

	err_str = strerror(errno);
	ft_printf("minishell: %s: %s: %s\n", args[0], args[1], err_str);
}

char	**malloc_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	return (new_envp);
}

char	**envp_dup(char **envp)
{
	char	**res;
	int		i;

	res = malloc_envp(envp);
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
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
		return (NULL);
	}
	free(prompt);
	prompt = temp;
	return (prompt);
}
