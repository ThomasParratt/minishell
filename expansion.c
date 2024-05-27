/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/27 13:05:15 by tparratt         ###   ########.fr       */
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

void	expansion(t_mini *tokens, t_data *data)
{
	int		i;
	int		start;
	int		len;
	char	**new_tokens;
	char	*env_name;
	char	*env_value;

	i = 0;
	new_tokens = malloc_envp(tokens->metaed);
	while (tokens->metaed[i])
	{
		len = ft_strlen(tokens->metaed[i]);
		if (ft_strchr(tokens->metaed[i], '$'))
		{
			start = 0;
			while (tokens->metaed[i][start] != '$')
				start++;
			start++;
			env_name = ft_substr(tokens->metaed[i], start, len - start);
			if (!env_name)
				malloc_failure();
			env_value = ft_getenv(data->envp, env_name);
			if (!env_value)
				malloc_failure();
			new_tokens[i] = ft_strdup(env_value);
			if (!new_tokens[i])
				malloc_failure();
			free(env_name);
			free(env_value);
		}
		else
			new_tokens[i] = ft_strdup(tokens->metaed[i]);
		i++;
	}
	new_tokens[i] = NULL;
	free(tokens->metaed);
	//print_2d(new_tokens);
	tokens->metaed = new_tokens;
}

