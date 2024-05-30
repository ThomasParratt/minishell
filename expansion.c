/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/30 17:42:25 by tparratt         ###   ########.fr       */
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
		while (str[len] != '$' && str[len] != '\0' && str[len] != '"'  && str[len] != ' ')
			len++;
	}
	else
	{
		while (str[len] != '$' && str[len] != '\0' && str[len] != '"')
			len++;
	}
	len = len - start;
	ft_printf("start = %d\n", start);
	ft_printf("len = %d\n", len);
	substring = ft_substr(str, start, len);
	ft_printf("substring = %s\n", substring);
	return (substring);
}

//Until we reach a $ or null terminator - join that
//If we reach a $ - do what I have already until we reach a $ or null terminator OR WHITESPACE
void	expansion(t_mini *line, t_data *data)
{
	int		i;
	int		j;
	char	**new_tokens;
	char	*env_value;
	//int		dollar_count;
	char	*substring;
	int		loop;

	ft_printf("metaed BEFORE expansion:\n");
	print_2d(line->metaed);
	ft_printf("\n");
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
					ft_printf("env_value = %s\n", env_value);
					if (!env_value)
					{
						if (loop == 0)
							new_tokens[i] = ft_strdup("");
						else
							new_tokens[i] = join_and_free(new_tokens[i], "");
					}
					else
					{
						if (loop == 0)
						{
							ft_printf("new_tokens[i] doesn't exist\n");
							new_tokens[i] = ft_strdup(env_value);
						}
						else
						{
							ft_printf("new_tokens[i] already exists\n");
							new_tokens[i] = join_and_free(new_tokens[i], env_value);
						}
					}
				}
				else
				{
					substring = get_substring(line->metaed[i], j); //until we reach a $ or null terminator OR WHITESPACE;
					if (!new_tokens[i])
						new_tokens[i] = ft_strdup(substring);
					else
						new_tokens[i] = join_and_free(new_tokens[i], substring);
				}
				j += ft_strlen(substring);
				free(substring);
				loop++;
			}
		}
		else
		{
			//remove single and double quotes from the beginning and end of string
			//remove double quotes from inside the string
			new_tokens[i] = ft_strdup(line->metaed[i]);
			if (!new_tokens[i])
				malloc_failure();
		}
		ft_printf("new_tokens[i] = %s\n", new_tokens[i]);
		i++;
	}
	ft_printf("\n");
	new_tokens[i] = NULL;
	free_2d(line->metaed);
	line->metaed = new_tokens;
	ft_printf("metaed AFTER expansion:\n");
	print_2d(line->metaed);
	ft_printf("\n");
}

