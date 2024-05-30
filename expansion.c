/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/30 12:41:19 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle $?
//handle where he '$' doesn't come immediately after the '"' e.g. "hello $VAR"
// e.g. "$VAR hello" "hello$VARhello" "$VARhello" "hello$VAR"
//handle string beginning and ending in single quotes, i.e. remove the quotes

/*static int	get_len(t_mini *line, int i, int j)
{
	int	len;
	int	dollar_count;
	int	quote_count;

	len = 0;
	dollar_count = 0;
	quote_count = 0;
	while (line->metaed[i][len] && quote_count < 2 && dollar_count < (j + 2)) //this is weird
	{
		if (line->metaed[i][len] == '$')
			dollar_count++;
		if (line->metaed[i][len] == '"')
			quote_count++;
		if (dollar_count < (j + 2) && quote_count < 2)
			len++;
	}
	ft_printf("len = %d\n", len);
	return (len);
}

static int	get_start(t_mini *line, int i, int j)
{
	int	start;
	int	count;

	start = 0;
	count = 0;
	while (line->metaed[i][start])
	{
		if (line->metaed[i][start] == '$')
			count++;
		if (count == j + 1)
			break ;
		start++;
	}
	start++;
	ft_printf("start = %d\n", start);
	return (start);
}

static char	*get_env_value(t_mini *line, int i, int j, t_data *data)
{
	int		start;
	int		len;
	char	*env_name;
	char	*env_value;

	start = get_start(line, i, j);
	len = get_len(line, i, j);
	env_name = ft_substr(line->metaed[i], start, len - start);
	if (!env_name)
		malloc_failure();
	ft_printf("env_name = %s\n", env_name);
	env_value = ft_getenv(data->envp, env_name);
	if (!env_value)
		return (NULL);
	free(env_name);
	return (env_value);
}

static int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}*/

/*static void	expand(char *new_tokens, char *str)
{
		new_tokens = join_and_free(new_tokens, str);
}*/

// get start, get len, ft_substr
static char	*get_substring(char *str, int j)
{
	int		start;
	int		len;
	char	*substring;

	start = j;
	len = j;
	while (str[len] != '$' && str[len] != '\0' && str[len] != ' ' && str[len] != '"')
		len++;
	ft_printf("len = %d\n", len);
	len = len - start;
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
	//int	dollar_count;
	char	*substring;
	int		index;

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
			index = 0;
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
						if (!new_tokens[i])
							new_tokens[i] = ft_strdup("");
						else
							new_tokens[i] = join_and_free(new_tokens[i], "");
					}
					else
					{
						if (!new_tokens[i])
							new_tokens[i] = ft_strdup(env_value);
						else
							new_tokens[i] = join_and_free(new_tokens[i], env_value);
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
				j = j + ft_strlen(substring) + 1; //problem with iteration
				free(substring);
			}
			/*dollar_count = count_char(line->metaed[i], '$');
			ft_printf("dollar count = %d\n", dollar_count);
			j = 0;
			while (j < dollar_count)
			{
				ft_printf("j = %d\n", j);
				env_value = get_env_value(line, i, j, data);
				if (!env_value)
					expand(new_tokens, j, i, "");
				else
					expand(new_tokens, j, i, env_value);
				ft_printf("new_tokens[i] = %s\n", new_tokens[i]);
				if (!new_tokens[i])
					malloc_failure();
				free(env_value);
				j++;
			}*/
		}
		else
		{
			//remove quotes
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

