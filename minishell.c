/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/18 12:16:47 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], tokens[0]);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		//printf ("%d\n", access(paths[i], F_OK));
		if (access(paths[i], F_OK) == 0)
			return (ft_strdup(paths[i])); // path to executable folder including executable
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
		while (1)
		{
			getcwd(cwd, sizeof(cwd));
			username = getenv("USER");
			hostname = getenv("HOSTNAME");
			prompt = create_prompt(username, hostname, cwd);
			line_read = readline(prompt);
			ft_printf("line_read = %s\n\n", line_read);
			add_history(line_read);
			tokens = ft_split(line_read, ' ');
			if (!contains_pipe(line_read))
				execute_command(tokens, envp);
			else if (contains_pipe(line_read))
			{
				//execute pipe
			}
			free(line_read);
			free(prompt);
		}
	}
	return (0);
}

