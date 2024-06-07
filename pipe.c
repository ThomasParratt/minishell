/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/07 15:09:31 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_output_append(t_tokens *token, int i, int j)
{
	int	fd;

	fd = open(token[i].redirect[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
		exit(1);
	close(fd);
}

static void	redirect_output(t_tokens *token, int i, int j)
{
	int	fd;

	fd = open(token[i].redirect[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
		exit(1);
	close(fd);
}

static void	redirect_input(t_tokens *token, int i, int j)
{
	int	fd;

	fd = open(token[i].redirect[j + 1], O_RDONLY);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		exit(1);
	close(fd);
}

static void	redirections(t_tokens *token, int i)
{
	int	j;

	j = 0;
	while (token[i].redirect[j])
	{
		if (ft_strncmp(token[i].redirect[j], "<", 2) == 0)
			redirect_input(token, i, j);
		else if (ft_strncmp(token[i].redirect[j], ">", 2) == 0)
			redirect_output(token, i, j);
		else if (ft_strncmp(token[i].redirect[j], ">>", 3) == 0)
			redirect_output_append(token, i, j);
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
			redirections(token, i);
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
