/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/03 15:11:24 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_substring(char *str, int j)
{
	int		start;
	int		len;
	char	*substring;

	start = j;
	len = j;
	if (str[start - 1] == '$')
	{
		while (str[len] != '$' && str[len] != '\0' && str[len] != '"' && str[len] != ' ')
			len++;
	}
	else
	{
		while (str[len] != '$' && str[len] != '\0' && str[len] != '"')
			len++;
	}
	len = len - start;
	substring = ft_substr(str, start, len);
	if (!substring)
		malloc_failure();
	return (substring);
}

static void	dup_or_join(char **new_tokens, int loop, int i, char *str)
{
	if (loop == 0)
		new_tokens[i] = ft_strdup(str);
	else
		new_tokens[i] = join_and_free(new_tokens[i], str);
}

static void	duplicate(t_mini *line, char **new_tokens, int i)
{
	int	len;

	len = ft_strlen(line->metaed[i]);
	if (!ft_isprint(line->metaed[i][0]) && !ft_isprint(line->metaed[i][len]))
		new_tokens[i] = ft_substr(line->metaed[i], 1, len - 1);
	else
		new_tokens[i] = ft_strdup(line->metaed[i]);
	if (!new_tokens[i])
		malloc_failure();
}

static void	expand(t_mini *line, char **new_tokens, t_data *data, int i)
{
	int		j;
	int		loop;
	char	*substring;
	char	*env_value;

	j = 0;
	loop = 0;
	if (line->metaed[i][0] == '"')
		j++;
	while (line->metaed[i][j] && line->metaed[i][j] != '"')
	{
		if (line->metaed[i][j] == '$')
		{
			j++;
			if (line->metaed[i][j] == '?')
			{
				dup_or_join(new_tokens, loop, i, ft_itoa(data->err_num));
				j++;
				break ;
			}
			substring = get_substring(line->metaed[i], j);
			env_value = ft_getenv(data->envp, substring);
			if (!env_value)
				dup_or_join(new_tokens, loop, i, "");
			else
				dup_or_join(new_tokens, loop, i, env_value);
			free(env_value);
		}
		else
		{
			substring = get_substring(line->metaed[i], j);
			dup_or_join(new_tokens, loop, i, substring);
		}
		j += ft_strlen(substring);
		free(substring);
		loop++;
	}
}

void	expansion(t_mini *line, t_data *data)
{
	int		i;
	char	**new_tokens;

	i = 0;
	new_tokens = malloc_2d(line->metaed);
	while (line->metaed[i])
	{
		if (ft_strchr(line->metaed[i], '$') && line->metaed[i][0] != '\'' && line->metaed[i][ft_strlen(line->metaed[i])] != '\'')
			expand(line, new_tokens, data, i);
		else
			duplicate(line, new_tokens, i);
		i++;
	}
	new_tokens[i] = NULL;
	free_2d(line->metaed);
	line->metaed = new_tokens;
}

