/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/03 15:22:33 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(char **tokens, char **envp)
{
	int		id;
	char	*path_str;

	if (!ft_strncmp(tokens[0], "echo", 5) && !ft_strncmp(tokens[1], "-n", 3))
		echo(tokens);
	else if (!ft_strncmp(tokens[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(tokens[0], "cd", 3))
		cd(tokens);
	else
	{
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

//Ctrl+C sends SIGINT. Ctrl+\ sends SIGQUIT
static void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;
	char	*prompt;
	char	**tokens;

	argv = NULL;
	if (argc == 1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		while (1)
		{
			prompt = create_prompt();
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
				return (0);
			//parse_tokens();
			execute(line_read, tokens, envp);
			free(line_read);
			free_split(tokens);
		}
	}
	return (0);
}
