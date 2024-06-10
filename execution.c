/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/10 12:23:07 by tparratt         ###   ########.fr       */
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

void	execute(t_tokens *token, t_mini *line)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	int		in_fd;
	int		status;

	in_fd = STDIN_FILENO;
	i = 0;
	while (i < line->pipe_num)
	{
		line->flag = 0;
		if (i < line->pipe_num - 1 && pipe(fd) == -1)
			exit(1);
		if (is_builtin(token, i))
        {
            redirections(token, i); // Handle redirections for the built-in
            execute_builtin(token, line, i); // Execute the built-in
			line->flag = 1;
            i++; // Move to the next command in the pipeline
            continue; // Skip forking for built-in commands
        }
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
			if (execve(get_path(token[i].command, line->envp), token[i].command, line->envp) == -1)
				exit(1);

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
		wait(&status);
		if (line->flag == 0)
		{
			if (WIFEXITED(status))
				line->err_num = WEXITSTATUS(status);
		}
		i++;
	}
}
