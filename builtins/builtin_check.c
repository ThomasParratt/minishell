/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:47:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/27 16:31:59 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_tokens(t_mini *line, t_data *data, char *line_read)
{
	if (!ft_strncmp(line->metaed[0], "echo", 5))
		echo(line->metaed);
	else if (!ft_strncmp(line->metaed[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(line->metaed[0], "cd", 3))
		cd(line->metaed, data);
	else if (!ft_strncmp(line->metaed[0], "env", 4))
		env(line->metaed, data);
	else if (!ft_strncmp(line->metaed[0], "exit", 5))
		exit_cmd(line->metaed, data);
	else if (!ft_strncmp(line->metaed[0], "export", 7))
		export_cmd(line->metaed, data);
	else if (!ft_strncmp(line->metaed[0], "unset", 6))
		unset_cmd(line->metaed, data);
	else
		execute(line_read, line->metaed, data->envp);
}
