/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/03 17:04:59 by tparratt         ###   ########.fr       */
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

// static void	id2(pid_t id1, int *fd, t_tokens *token, t_data *data)
// {
// 	pid_t	id2;

// 	id2 = fork();
// 	if (id2 == 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		if (execve(get_path(token[1].command, data->envp), token[1].command, data->envp) == -1)
// 			exit(1);
// 	}
// 	else
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 		waitpid(id1, NULL, 0);
// 		waitpid(id2, NULL, 0);
// 	}
// }

void	execute_pipe(t_tokens *tokens, t_data *data, t_mini *line)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	int		in_fd;

	i = 0;
	in_fd = STDIN_FILENO; // Initially, the input is from the standard input
	ft_printf("pipe_num = %d\n", line->pipe_num);
	while (i < line->pipe_num)
	{
		if (i < line->pipe_num - 1)
			pipe(fd); // Create a pipe for all but the last command
		// add builtin check here?
		pid = fork();
		if (pid == 0) // Child process
		{
			if (i > 0)
			{
				// Get input from the previous command
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (i < line->pipe_num - 1)
			{
				// Send output to the next command
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			// Execute the command
			if (execute_builtin(tokens, data) == 0) // incorrect
				exit(1);
			if (execve(get_path(tokens[i].command, data->envp), tokens[i].command, data->envp) == -1)
				exit(1);
		}
		else // Parent process
		{
			if (i > 0)
				close(in_fd);
			if (i < line->pipe_num - 1)
			{
				close(fd[1]);
				in_fd = fd[0];
			}
		}
		i++;
	}
	// Wait for all child processes to finish
	i = 0;
	while (i < line->pipe_num)
	{
		wait(NULL);
		i++;
	}
}

void	execute_command(t_tokens *token, t_data *data)
{
	int		id;
	char	*path_str;

	id = fork();
	if (id == 0)
	{
		path_str = get_path(token[0].command, data->envp);
		if (execute_builtin(token, data) == 0)
			exit(1);
		execve(path_str, token[0].command, data->envp);
		free(path_str);
		exit(1);
	}
	else
		wait(NULL);
}

// char	**execute(char *line_read, char **tokens, char **envp)
// {
// 	char	**pipe_cmds;
// 	t_cmd	*cmds;

// 	cmds = malloc(sizeof(t_cmd));
// 	if (!contains_pipe(line_read))
// 		execute_command(tokens, envp);
// 	else if (contains_pipe(line_read))
// 	{
// 		pipe_cmds = ft_split(line_read, '|');
// 		cmds->cmd1 = ft_split(pipe_cmds[0], ' ');
// 		cmds->path1 = get_path(cmds->cmd1, envp);
// 		cmds->cmd2 = ft_split(pipe_cmds[1], ' ');
// 		cmds->path2 = get_path(cmds->cmd2, envp);
// 		free_2d(pipe_cmds);
// 		execute_pipe(cmds, envp);
// 		free_2d(cmds->cmd1);
// 		free_2d(cmds->cmd2);
// 		free(cmds->path1);
// 		free(cmds->path2);
// 		free(cmds);
// 	}
// 	return (envp);
// }
