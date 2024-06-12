/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 11:27:08 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_lvl_check(t_mini *line)
{
	char	*shell_value;
	int		value;
	char	*str;
	char	*str_to_export;

	shell_value = get_env_value(line->envp, "SHLVL", line);
	value = ft_atoi(shell_value);
	value++;
	str = ft_itoa(value);
	str_to_export = ft_strjoin("SHLVL=", str);
	export(str_to_export, line);
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
		if (is_builtin(&token[i]))
		{
			redirections(&token[i]); // Handle redirections for the built-in
			execute_builtin(&token[i], line); // Execute the built-in
			line->flag = 1;
			i++; // Move to the next command in the pipeline
			continue ; // Skip forking for built-in commands
		}
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0) // Child process
		{
			if (!ft_strncmp(token[i].command[0], "./minishell", 11))
				shell_lvl_check(line);
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
			redirections(&token[i]);
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
