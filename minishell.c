/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/26 16:07:46 by tparratt         ###   ########.fr       */
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

char	*get_path(char **tokens)
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
	int		i;

	i = 0;
	if (!contains_pipe(line_read))
		execute_command(tokens, envp);
	else if (contains_pipe(line_read))
	{
		ft_printf("Command includes pipe\n");
		//execute pipe
	}
}

/*void receive_signal(int sig)
{
	if (sig == SIGINT)
		rl_redisplay();
	if (sig == SIGQUIT)
		return ;
}

void	handle_signals(char *line_read)
{
	signal(SIGINT, receive_signal);
	signal(SIGQUIT, receive_signal);
	while (1)
        pause();
}*/

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
				ft_printf("\nexit\n");
				return (0);
			}
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

