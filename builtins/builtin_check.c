/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:47:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/27 13:09:23 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_tokens(t_mini *tokens, t_data *data, char *line_read)
{
	if (!ft_strncmp(tokens->metaed[0], "echo", 5))
		echo(tokens->metaed);
	else if (!ft_strncmp(tokens->metaed[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(tokens->metaed[0], "cd", 3))
		cd(tokens->metaed, data);
	else if (!ft_strncmp(tokens->metaed[0], "env", 4))
		env(tokens->metaed, data);
	else if (!ft_strncmp(tokens->metaed[0], "exit", 5))
		exit_cmd(tokens->metaed, data);
	else if (!ft_strncmp(tokens->metaed[0], "export", 7))
		export_cmd(tokens->metaed, data);
	else if (!ft_strncmp(tokens->metaed[0], "unset", 6))
		unset_cmd(tokens->metaed, data);
	else
		execute(line_read, tokens->metaed, data->envp);
}
