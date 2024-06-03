/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/03 10:45:59 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle $?
//handle where he '$' doesn't come immediately after the '"' e.g. "hello $VAR"
// e.g. "$VAR hello" "hello$VARhello" "$VARhello" "hello$VAR"
//handle string beginning and ending in single quotes, i.e. remove the quotes


// get start, get len, ft_substr
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

void	expansion(t_mini *line, t_data *data)
{
	int		i;
	int		j;
	char	**new_tokens;
	char	*env_value;
	char	*substring;
	int		loop;

	i = 0;
	new_tokens = malloc_2d(line->metaed);
	while (line->metaed[i])
	{
		if (ft_strchr(line->metaed[i], '$') && line->metaed[i][0] != '\'' && line->metaed[i][ft_strlen(line->metaed[i])] != '\'')
		{
			j = 0;
			loop = 0;
			if (line->metaed[i][0] == '"')
				j++;
			while (line->metaed[i][j] && line->metaed[i][j] != '"')
			{
				if (line->metaed[i][j] == '$')
				{
					j++;
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
		else
		{
			// replace unprintable character with $
			new_tokens[i] = ft_strdup(line->metaed[i]);
			if (!new_tokens[i])
				malloc_failure();
		}
		i++;
	}
	new_tokens[i] = NULL;
	free_2d(line->metaed);
	line->metaed = new_tokens;
}

