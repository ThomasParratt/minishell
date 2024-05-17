/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:47:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/16 13:29:38 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**check_builtins(char **tokens, char **envp, char *line_read)
{
	if (!ft_strncmp(tokens[0], "echo", 5))
		echo(tokens);
	else if (!ft_strncmp(tokens[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(tokens[0], "cd", 3))
		envp = cd(tokens, envp);
	else if (!ft_strncmp(tokens[0], "env", 4))
		env(tokens, envp);
	else if (!ft_strncmp(tokens[0], "exit", 5))
		exit_cmd(tokens);
	else if (!ft_strncmp(tokens[0], "export", 7))
		envp = export_cmd(tokens, envp);
	else if (!ft_strncmp(tokens[0], "unset", 6))
	{
		if (!tokens[1])
			return (envp);
		envp = unset(tokens[1], envp);
	}
	else
		execute(line_read, tokens, envp);
	return (envp);
}