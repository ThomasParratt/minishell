/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:47:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/22 12:22:13 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_tokens(char **tokens, t_data *data, char *line_read)
{
	if (!ft_strncmp(tokens[0], "echo", 5))
		echo(tokens);
	else if (!ft_strncmp(tokens[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(tokens[0], "cd", 3))
		cd(tokens, data);
	else if (!ft_strncmp(tokens[0], "env", 4))
		env(tokens, data);
	else if (!ft_strncmp(tokens[0], "exit", 5))
		exit_cmd(tokens, data);
	else if (!ft_strncmp(tokens[0], "export", 7))
		export_cmd(tokens, data);
	else if (!ft_strncmp(tokens[0], "unset", 6))
		unset_cmd(tokens, data);
	else
		execute(line_read, tokens, data->envp);
}
