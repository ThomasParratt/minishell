/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/16 14:09:14 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

char	*create_prompt(char *str1, char *str2, char *str3)
{
	size_t	len;
	char	*res;

	len = ft_strlen(str1) + ft_strlen(str2) + 3;
	res = ft_strdup("");
	if (!res)
		exit(EXIT_FAILURE);
	res = ft_strjoin(res, str1);
	res = ft_strjoin(res, "@");
	res = ft_strjoin(res, str2);
	res = ft_strjoin(res, ":");
	res = ft_strjoin(res, str3);
	res = ft_strjoin(res, "$ ");
	return (res);
}

void	execute_pipe(char **cmd1, char **cmd2)
{
	int		fd[2];
	pid_t	id;

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve("/bin/ls", cmd1, NULL);
		perror("execve");
		exit(1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
		execve("/usr/bin/wc", cmd2, NULL);
		perror("execve");
		exit(1);
	}
}

char	*get_path(char **tokens)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = getenv("PATH");
	paths = ft_split(path_pointer, ':');
	i = 0;
	while (paths[i])
	{
		strcat(paths[i], "/");
		strcat(paths[i], tokens[0]);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		//printf("%s\n", paths[i]);
		//printf ("%d\n", access(paths[i], F_OK));
		if (access(paths[i], F_OK) == 0)
			return (ft_strdup(paths[i])); // path to executable folder including executable
		i++;
	}
	ft_printf("Executable folder not found\n");
	return (NULL);
}

void	execute_command(char **tokens)
{
	int		id;
	char	*path = NULL;

	id = fork();
	if (id == 0)
	{
		path = get_path(tokens);
		ft_printf("%s\n", path);
		/*path = ft_strdup("/bin/");
		if (!path)
			exit(EXIT_FAILURE);
		path = ft_strjoin(path, tokens[0]);*/
		execve(path, tokens, NULL);
		free(path);
		exit(0);
	}
	else
		wait(NULL);
}

int	check_line_read(char *line_read)
{
	int		i;

	i = 0;
	
	if (ft_strchr(line_read, '|'))
	{
		//pipe found
		return (1);
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*line_read;
	char	cwd[1024];
	char	*username;
    char	*hostname;
	char	*prompt;
	char	**tokens;

	argv = NULL;
	if (argc == 1)
	{
		int i = 0;
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		while (1)
		{
			getcwd(cwd, sizeof(cwd));
			username = getenv("USER");
			hostname = getenv("HOSTNAME");
			prompt = create_prompt(username, hostname, cwd);
			line_read = readline(prompt);
			add_history(line_read);
			tokens = ft_split(line_read, ' ');
			if (!check_line_read(line_read))
				execute_command(tokens);
			if (check_line_read(line_read))
			{
				char **pipe_cmds = ft_split(line_read, '|');
				// now need to split each seperate string in pipe_cmds in order to get args for cmd1 and cmd2
				// deal with space at the beginning of pipe_cmds[1]
				int i = 0;
				while (pipe_cmds[i])
				{
					ft_printf("%s\n", pipe_cmds[i]);
					i++;
				}
				char *cmd1[] = {pipe_cmds[0], NULL};
				char *cmd2[] = {pipe_cmds[1], NULL};
				execute_pipe(cmd1, cmd2);
			}
			else
				wait(NULL);
			free(line_read);
			free(prompt);
		}
	}
	return (0);
}

