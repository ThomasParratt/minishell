/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:47:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/30 17:27:55 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_tokens(t_tokens *token, t_data *data, char *line_read, t_mini *line)
{
	int	i;

	i = 0;
	while (i < line->pipe_num)
	{
		if (!ft_strncmp(token[i].command[0], "echo", 5))
		{
			ft_printf("my echo\n");
			echo(token[i].command);
		}
		else if (!ft_strncmp(token[i].command[0], "pwd", 4))
			pwd();
		else if (!ft_strncmp(token[i].command[0], "cd", 3))
			cd(token[i].command, data);
		else if (!ft_strncmp(token[i].command[0], "env", 4))
			env(token[i].command, data);
		else if (!ft_strncmp(token[i].command[0], "exit", 5))
			exit_cmd(token[i].command, data);
		else if (!ft_strncmp(token[i].command[0], "export", 7))
			export_cmd(token[i].command, data);
		else if (!ft_strncmp(token[i].command[0], "unset", 6))
			unset_cmd(token[i].command, data);
		else
			execute(line_read, token[i].command, data->envp);
		i++;
	}
}
