/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:00:48 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/29 14:36:24 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tab)
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

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
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