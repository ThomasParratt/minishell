/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/18 13:40:50 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(void)
{
	char	cwd[1024];
	char	*username;
    char	*hostname;
	size_t	len;
	char	*res;

	getcwd(cwd, sizeof(cwd));
	username = getenv("USER");
	hostname = getenv("HOSTNAME");
	len = ft_strlen(username) + ft_strlen(hostname) + 3;
	res = ft_strdup("");
	if (!res)
		exit(EXIT_FAILURE);
	res = ft_strjoin(res, username);
	free(res);
	res = ft_strjoin(res, "@");
	free(res);
	res = ft_strjoin(res, hostname);
	free(res);
	res = ft_strjoin(res, ":");
	free(res);
	res = ft_strjoin(res, cwd);
	free(res);
	res = ft_strjoin(res, "$ ");
	return (res);
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
		exit(0);
	}
	else
		wait(NULL);
}

int	contains_pipe(char *line_read)
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

void	parse_input(char *line_read, char **tokens, char **envp)
{
	if (!contains_pipe(line_read))
		execute_command(tokens, envp);
	else if (contains_pipe(line_read))
	{
		//execute pipe
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
		}
	}
	return (0);
}

