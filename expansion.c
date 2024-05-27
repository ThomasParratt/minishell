/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/27 17:11:14 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle $?
//handle where he '$' doesn't come immediately after the '"' e.g. "hello $VAR"
// e.g. "$VAR hello" "hello$VARhello" "$VARhello" "hello$VAR"
//handle string beginning and ending in single quotes, i.e. remove the quotes
/*char	**expansion(char **tokens, t_data *data)
{
	int		i;
	int		j;
	int		token_len;
	char	*env_name;
	char	**new_tokens;
	char	*env_value;

	i = 0;
	new_tokens = malloc_envp(tokens);
	if (!new_tokens)
		malloc_failure();
	while (tokens[i])
	{
		token_len = ft_strlen(tokens[i]);
		if (tokens[i][0] == '$')
		{
			env_name = malloc(sizeof(char) * ft_strlen(tokens[i]));
			if (!env_name)
				malloc_failure();
			j = 0;
			while (j < token_len)
			{
				env_name[j] = tokens[i][j + 1];
				j++;
			}
			env_name[j] = '\0';
			env_value = ft_getenv(data->envp, env_name);
			if (!env_value)
				malloc_failure();
			new_tokens[i] = ft_strdup(env_value);
			if (!new_tokens[i])
				malloc_failure();
			free(env_name);
			free(env_value);
		}
		else if (tokens[i][0] == '"' && tokens[i][1] == '$' && tokens[i][token_len - 1] == '"')
		{
			env_name = malloc(sizeof(char) * (token_len - 2));
			if (!env_name)
				malloc_failure();
			j = 0;
			while (j < token_len - 3)
			{
				env_name[j] = tokens[i][j + 2];
				j++;
			}
			env_name[j] = '\0';
			env_value = ft_getenv(data->envp, env_name);
			new_tokens[i] = ft_strdup(env_value);
			if (!new_tokens[i])
				malloc_failure();
			free(env_name);
			free(env_value);
		}
		else if (tokens[i][0] == '\'' && tokens[i][ft_strlen(tokens[i]) - 1] == '\'')
		{
			
		}
		else
			new_tokens[i] = ft_strdup(tokens[i]);
		i++;
	}
	new_tokens[i] = NULL;
	//print_2d(tokens);
	free_2d(tokens);
	//print_2d(new_tokens);
	return (new_tokens);
}*/

void	expansion(t_mini *line, t_data *data)
{
	int		i;
	int		start;
	int		len;
	char	**new_tokens;
	char	*env_name;
	char	*env_value;

	//print_2d(line->metaed);
	i = 0;
	new_tokens = malloc_2d(line->metaed);
	while (line->metaed[i])
	{
		//len = ft_strlen(line->metaed[i]);
		//data->flag = 0;
		if (ft_strchr(line->metaed[i], '$'))
		{
			start = 0;
			while (line->metaed[i][start] != '$') //this only works if $ is first in the string
				start++;
			start++;
			len = 1;
			while (line->metaed[i][len] && line->metaed[i][len] != '$' && line->metaed[i][len] != ' ')
				len++;
			env_name = ft_substr(line->metaed[i], start, len - start);
			if (!env_name)
				malloc_failure();
			ft_printf("env_name = %s\n", env_name);
			env_value = ft_getenv(data->envp, env_name);
			if (!env_value)
			{
				new_tokens[i] = ft_strdup("");
				if (!new_tokens[i])
					malloc_failure();
				free(env_name);
				free(env_value);
			}
			else
			{
				new_tokens[i] = ft_strdup(env_value);
				if (!new_tokens[i])
					malloc_failure();
				free(env_name);
				free(env_value);
			}
		}
		else
			new_tokens[i] = ft_strdup(line->metaed[i]);
		i++;
	}
	new_tokens[i] = NULL;
	free_2d(line->metaed);
	line->metaed = new_tokens;
	//print_2d(line->metaed);
}

