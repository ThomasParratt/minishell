/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/28 11:19:09 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle $?
//handle where he '$' doesn't come immediately after the '"' e.g. "hello $VAR"
// e.g. "$VAR hello" "hello$VARhello" "$VARhello" "hello$VAR"
//handle string beginning and ending in single quotes, i.e. remove the quotes

/*static int	count_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
	}
	return (i);
}*/

void	expansion(t_mini *line, t_data *data)
{
	int		i;
	int		start;
	int		len;
	char	**new_tokens;
	char	*env_name;
	char	*env_value;
	int		dollar_count;
	int		quote_count;

	ft_printf("metaed BEFORE expansion:\n");
	print_2d(line->metaed);
	ft_printf("\n");
	i = 0;
	new_tokens = malloc_2d(line->metaed);
	while (line->metaed[i])
	{
		if (line->metaed[i][0] == '\'' && line->metaed[i][ft_strlen(line->metaed[i]) - 1] == '\'')
			new_tokens[i] = ft_strdup(line->metaed[i]);
		else if (ft_strchr(line->metaed[i], '$'))
		{
			start = 0;
			while (line->metaed[i][start] != '$')
				start++;
			start++;
			len = 0;
			dollar_count = 0;
			quote_count = 0;
			while (line->metaed[i][len] && quote_count < 2 && dollar_count < 2) //this is weird
			{
				if (line->metaed[i][len] == '$')
					dollar_count++;
				if (line->metaed[i][len] == '"')
					quote_count++;
				if (dollar_count < 2 && quote_count < 2)
					len++;
			}
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
	ft_printf("\n");
	new_tokens[i] = NULL;
	free_2d(line->metaed);
	line->metaed = new_tokens;
	ft_printf("metaed AFTER expansion:\n");
	print_2d(line->metaed);
	ft_printf("\n");
}


