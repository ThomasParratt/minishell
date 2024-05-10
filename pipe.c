/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/10 15:07:43 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_pipe(char *line_read)
{
	int		i;

	i = 0;
	if (ft_strchr(line_read, '|'))
		return (1);
	return (0);
}

static void	id2(pid_t id1, int *fd, t_cmd *cmds, char **envp)
{
	pid_t	id2;

	id2 = fork();
	if (id2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (execve(cmds->path2, cmds->cmd2, envp) == -1)
			exit(1);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(id1, NULL, 0);
		waitpid(id2, NULL, 0);
	}
}

void	execute_pipe(t_cmd *cmds, char **envp)
{
	int		fd[2];
	pid_t	id1;

	pipe(fd);
	id1 = fork();
	if (id1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(cmds->path1, cmds->cmd1, envp) == -1)
			exit(1);
	}
	else
		id2(id1, fd, cmds, envp);
}
