/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/29 14:04:53 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_prompt(void)
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

static char	*get_path(char **tokens)
{
	char	*path_pointer;
	char	**paths;
	int		i;
	char	*res;

	path_pointer = getenv("PATH");
	if (!path_pointer)
		return (NULL);
	paths = ft_split(path_pointer, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = join_and_free(paths[i], "/");
		paths[i] = join_and_free(paths[i], tokens[0]);
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
			free_split(paths);
			return (res);
		}
		i++;
	}
	free_split(paths);
	ft_printf("minishell: %s: command not found\n", tokens[0]);
	return (NULL);
}

static void	execute_command(char **tokens, char **envp)
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

static void	execute(char *line_read, char **tokens, char **envp)
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
			if (!line_read)
			{
				//Ctrl-D - prints '^D' before exit
				ft_printf("\n%sexit\n", prompt);
				return (0);
			}
			free(prompt);
			add_history(line_read);
			tokens = ft_split(line_read, ' ');
			execute(line_read, tokens, envp);
			free(line_read);
			free_split(tokens);
		}
	}
	return (0);
}

