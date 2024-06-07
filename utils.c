/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:00:48 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/07 14:11:00 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

void	malloc_failure(void)
{
	ft_putendl_fd("minishell: malloc failure", 2);
	exit(ENOMEM);
}

char	**malloc_2d(char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	return (new_arr);
}

char	**envp_dup(char **envp)
{
	char	**res;
	int		i;

	res = malloc_2d(envp);
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
			return (NULL);
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
