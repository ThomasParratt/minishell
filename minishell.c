/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/10 17:25:19 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(char **tokens, char **envp)
{
	int		id;
	char	*path_str;

	id = fork();
	if (id == 0)
	{
		path_str = get_path(tokens, envp);
		execve(path_str, tokens, envp);
		free(path_str);
		exit(1);
	}
	else
		wait(NULL);
}

char	**execute(char *line_read, char **tokens, char **envp)
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
		cmds->path1 = get_path(cmds->cmd1, envp);
		cmds->cmd2 = ft_split(pipe_cmds[1], ' ');
		cmds->path2 = get_path(cmds->cmd2, envp);
		free_2d(pipe_cmds);
		execute_pipe(cmds, envp);
		free_2d(cmds->cmd1);
		free_2d(cmds->cmd2);
		free(cmds->path1);
		free(cmds->path2);
		free(cmds);
	}
	return (envp);
}

static char	*create_prompt(char **envp)
{
	char	*cwd;
	char	*username;
	char	*hostname;
	char	*prompt;

	cwd = ft_getenv(envp, "PWD");
	if (!cwd)
		exit(1);
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
	free(cwd);
	prompt = join_and_free(prompt, "$ ");
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;
	char	*prompt;
	char	**tokens;

	argv = NULL;
	envp = envp_dup(envp);
	if (argc == 1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		while (1)
		{
			prompt = create_prompt(envp);
			line_read = readline(prompt);
			free(prompt);
			if (!line_read)
			{
				ft_printf("exit\n");
				return (0);
			}
			add_history(line_read);
			tokens = ft_split(line_read, ' ');
			if (!tokens)
			{
				free(line_read);
				return (0);
			}
			//parse_tokens();
			envp = check_builtins(tokens, envp, line_read);
			free(line_read);
			free_2d(tokens);
		}
	}
	return (0);
}
