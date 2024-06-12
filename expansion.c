/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 12:30:46 by tparratt         ###   ########.fr       */
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
		while (str[len] != '$' && str[len] != '\0' && (ft_isalnum(str[len]) || str[len] == '_'|| str[len] == '?' || is_whitespace(str[len])))
			len++;
	}
	else
	{
		while (str[len] != '$' && str[len] != '\0')
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
	ft_printf("new_tokens[i] = %s\n", new_tokens[i]);
}

static void	duplicate(t_mini *line, char **new_tokens, int i)
{
	int	j;

	if (ft_strchr(line->metaed[i], 7))
	{
		j = 0;
		while (line->metaed[i][j])
		{
			if (line->metaed[i][j] == 7)
			{
				line->metaed[i][j] = '$';
				break ;
			}
			j++;
		}
	}
	new_tokens[i] = ft_strdup(line->metaed[i]);
	if (!new_tokens[i])
		malloc_failure();
}

static void	expand(t_mini *line, char **new_tokens, int i)
{
	int		j;
	int		loop;
	char	*substring;
	char	*env_value;

	j = 0;
	loop = 0;
	ft_printf("line->metaed[i] = %s\n", line->metaed[i]);
	while (line->metaed[i][j])
	{
		if (line->metaed[i][j] == '$' &&
			(!ft_isalnum(line->metaed[i][j + 1]) && line->metaed[i][j + 1] != '_' && line->metaed[i][j + 1] != '?'))
		{
			ft_printf("ONLY DOLLARS\n");
			dup_or_join(new_tokens, loop, i, "$");
			j++;
			loop++;
			continue ;
		}
		else if (line->metaed[i][j] == '$' &&
			(ft_isalnum(line->metaed[i][j + 1]) || line->metaed[i][j + 1] == '_' || line->metaed[i][j + 1] == '?'))
		{
			ft_printf("SOMETHING TO EXPAND\n");
			j++;
			substring = get_substring(line->metaed[i], j);
			ft_printf("substring = %s\n", substring);
			env_value = get_env_value(line->envp, substring, line);
			if (!env_value)
				dup_or_join(new_tokens, loop, i, "");
			else
				dup_or_join(new_tokens, loop, i, env_value);
			free(env_value);
		}
		else
		{
			ft_printf("NOTHING TO EXPAND\n");
			substring = get_substring(line->metaed[i], j);
			ft_printf("substring = %s\n", substring);
			ft_printf("substring len = %d\n", ft_strlen(substring));
			dup_or_join(new_tokens, loop, i, substring);
		}
		j += ft_strlen(substring);
		free(substring);
		loop++;
	}
}

// static void	expand(t_mini *line, char **new_tokens, int i)
// {
// 	int		j;
// 	int		loop;
// 	char	*substring;
// 	char	*env_value;

// 	j = 0;
// 	loop = 0;
// 	while (line->metaed[i][j])
// 	{
// 		if (line->metaed[i][j] == '$')
// 		{
// 			if (ft_strlen(line->metaed[i]) == 1)
// 			{
// 				dup_or_join(new_tokens, loop, i, "$");
// 				break ;
// 			}
// 			else if (is_whitespace(line->metaed[i][j + 1]) || line->metaed[i][j + 1] == '?' || line->metaed[i][j + 1] == '\0' || line->metaed[i][j + 1] == '$')
// 			{
// 				j++;
// 				if (is_whitespace(line->metaed[i][j]))
// 					dup_or_join(new_tokens, loop, i, "$ ");
// 				else if (line->metaed[i][j] == '?')
// 					dup_or_join(new_tokens, loop, i, ft_itoa(line->err_num));
// 				else if (line->metaed[i][j] == '\0')
// 					dup_or_join(new_tokens, loop, i, "$");
// 				else if (line->metaed[i][j] == '$' && line->metaed[i][j + 1] == '?')
// 				{
// 					dup_or_join(new_tokens, loop, i, "$");
// 					dup_or_join(new_tokens, loop, i, ft_itoa(line->err_num));
// 					j++;
// 				}
// 				else if (line->metaed[i][j] == '$' && ft_isalpha(line->metaed[i][j + 1]))
// 					continue ;
// 				else if (line->metaed[i][j] == '$')
// 					dup_or_join(new_tokens, loop, i, "$$");
// 				j++;
// 				loop++;
// 				continue ;
// 			}
// 			else
// 			{
// 				j++;
// 				substring = get_substring(line->metaed[i], j);
// 				env_value = get_env_value(line->envp, substring);
// 				if (!env_value)
// 					dup_or_join(new_tokens, loop, i, "");
// 				else
// 					dup_or_join(new_tokens, loop, i, env_value);
// 				free(env_value);
// 			}
// 		}
// 		else
// 		{
// 			substring = get_substring(line->metaed[i], j);
// 			dup_or_join(new_tokens, loop, i, substring);
// 		}
// 		j += ft_strlen(substring);
// 		free(substring);
// 		loop++;
// 	}
// }

void	expansion(t_mini *line)
{
	int		i;
	char	**new_tokens;

	i = 0;
	new_tokens = malloc_2d(line->metaed);
	while (line->metaed[i])
	{
		if (ft_strchr(line->metaed[i], '$'))
			expand(line, new_tokens, i);
		else
			duplicate(line, new_tokens, i);
		i++;
	}
	new_tokens[i] = NULL;
	free_2d(line->metaed);
	line->metaed = new_tokens;
}