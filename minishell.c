/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/26 10:10:33 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
		i++;
	}
}

void	execute_pipe(t_cmd *cmds, char **envp)
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
		execve(cmds->path1, cmds->cmd1, envp);
		perror("execve");
		exit(1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
		execve(cmds->path2, cmds->cmd2, envp);
		perror("execve");
		exit(1);
	}
}

char	*join_and_free(char *prompt, char *str)
{
	char	*temp;

	temp = ft_strjoin(prompt, str);
	if (!temp)
	{
		free(prompt);
		return (NULL);
	}
	free(prompt);
	prompt = temp;
	return (prompt);
}

char	*create_prompt(void) 
{
	char	cwd[1024];
	char	*username;
	char	*hostname;
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) == NULL) 
	{
		perror("getcwd failed");
		return (NULL);
	}
	username = getenv("USER");
	if (!username)
		username = "unknown";
	hostname = getenv("HOSTNAME");
	if (!hostname)
		hostname = "unknown";
	prompt = ft_strdup(username);
	prompt = join_and_free(prompt, "@");
	prompt = join_and_free(prompt, hostname);
	prompt = join_and_free(prompt, ":");
	prompt = join_and_free(prompt, cwd);
	prompt = join_and_free(prompt, "$ ");
	return (prompt);
}

//need to sort out memory allocation and freeing in this function
char	*get_path(char **tokens)
{
	char	*path_pointer;
	char	**paths;
	int		i;
	char	*res;

	path_pointer = getenv("PATH");
	paths = ft_split(path_pointer, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], tokens[0]);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			res = ft_strdup(paths[i]);
			if (!res)
				exit(1);
			return (res);
		}
		i++;
	}
	ft_printf("Executable directory not found\n");
	return (NULL);
}

void	execute_command(char **tokens, char **envp)
{
	int		id;
	char	*path_str;

	id = fork();
	if (id == 0)
	{
		path_str = get_path(tokens);
		execve(path_str, tokens, envp);
		free(path_str);
		exit(1);
	}
	else
		wait(NULL);
}

int	contains_pipe(char *line_read)
{
	int		i;

	i = 0;
	if (ft_strchr(line_read, '|'))
		return (1);
	return (0);
}

void	parse_input(char *line_read, char **tokens, char **envp)
{
	char	**pipe_cmds;
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!contains_pipe(line_read))
		execute_command(tokens, envp);
	else if (contains_pipe(line_read))
	{
		pipe_cmds = ft_split(line_read, '|');
		cmds->cmd1 = ft_split(pipe_cmds[0], ' ');
		cmds->path1 = get_path(cmds->cmd1);
		cmds->cmd2 = ft_split(pipe_cmds[1], ' ');
		cmds->path2 = get_path(cmds->cmd2);
		free_split(pipe_cmds);
		execute_pipe(cmds, envp);
		free_split(cmds->cmd1);
		free_split(cmds->cmd2);
		free(cmds->path1);
		free(cmds->path2);
		free(cmds);
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*line_read;
	char	*prompt;
	char	**tokens;

	argv = NULL;
	if (argc == 1)
	{
		while (1)
		{
			prompt = create_prompt();
			line_read = readline(prompt);
			free(prompt);
			add_history(line_read);
			tokens = ft_split(line_read, ' ');
			parse_input(line_read, tokens, envp);
			free(line_read);
			free_split(tokens);
		}
	}
	return (0);
}

