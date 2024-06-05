/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/05 17:43:40 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	contains_pipe(char *line_read)
// {
// 	if (ft_strchr(line_read, '|'))
// 		return (1);
// 	return (0);
// }

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

static void	redirections(t_tokens *token, int i)
{
	int	j;
	int	input_fd;
	int	output_fd;

	j = 0;
	while (token[i].redirect[j])
	{
		if (strcmp(token[i].redirect[j], "<") == 0)
		{
			input_fd = open(token[i].redirect[j + 1], O_RDONLY);
			if (input_fd == -1 || dup2(input_fd, STDIN_FILENO) == -1)
				exit(1);
			close(input_fd);
			j++;
		}
		else if (strcmp(token[i].redirect[j], ">") == 0)
		{
			output_fd = open(token[i].redirect[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (output_fd == -1 || dup2(output_fd, STDOUT_FILENO) == -1)
				exit(1);
			close(output_fd);
			j++;
		}
		else if (strcmp(token[i].redirect[j], ">>") == 0)
		{
			output_fd = open(token[i].redirect[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (output_fd == -1 || dup2(output_fd, STDOUT_FILENO) == -1)
				exit(1);
			close(output_fd);
			j++;
		}
		j++;
	}
}

void	execute(t_tokens *token, t_data *data, t_mini *line)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	int		in_fd;

	in_fd = STDIN_FILENO;
	i = 0;
	while (i < line->pipe_num)
	{
		if (i < line->pipe_num - 1 && pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0) // Child process
		{
			redirections(token, i);
			if (in_fd != STDIN_FILENO) // Redirect input
			{
				if (dup2(in_fd, STDIN_FILENO) == -1)
					exit(1);
				close(in_fd);
			}
			if (i < line->pipe_num - 1) // Redirect output
			{
				close(fd[0]);
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					exit(1);
				close(fd[1]);
			}
			if (is_builtin(token, i))
			{
				execute_builtin(token, data, i);
				exit(0); // Exit child process after executing builtin
			}
			else
			{
				if (execve(get_path(token[i].command, data->envp), token[i].command, data->envp) == -1)
					exit(1);
			}
		}
		else // Parent process
		{
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			if (i < line->pipe_num - 1)
			{
				close(fd[1]); // close write end of pipe
				in_fd = fd[0]; // set read end of pipe
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



// void	execute_command(t_tokens *token, t_data *data)
// {
// 	int		id;
// 	char	*path_str;

// 	if (is_builtin(token, 0) == 1)
// 		execute_builtin(token, data, 0);
// 	else
// 	{
// 		id = fork();
// 		if (id == 0)
// 		{
// 			path_str = get_path(token[0].command, data->envp);
// 			execve(path_str, token[0].command, data->envp);
// 			free(path_str);
// 			exit(1);
// 		}
// 		else
// 			wait(NULL);
// 	}
// }

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
