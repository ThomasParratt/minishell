/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/05 17:47:19 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_prompt(void)
{
	char	*cwd;
	char	*username;
	char	*hostname;
	char	*prompt;

	cwd = getcwd(NULL, 0);
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

// static void	free_all(char *line_read, t_tokens *token, t_mini *line)
// {
// 	int	i;

// 	free(line_read);
// 	free_2d(line->metaed);
// 	i = 0;
// 	while (token[i].command && token[i].command[0])
// 	{
// 		free_2d(token[i].command);
// 		i++;
// 	}
// 	i = 0;
// 	while (token[i].redirect && token[i].redirect[0])
// 	{
// 		free_2d(token[i].redirect);
// 		i++;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	char		*line_read;
	char		*prompt;
	t_data		data;
	t_mini		line;
	t_tokens	*token;

	argv = NULL;
	data.err_num = 0;
	data.envp = envp_dup(envp);
	if (!data.envp)
		malloc_failure();
	export("OLDPWD", &data);
	set_term_attr();
	if (argc == 1)
	{
		struct sigaction	sa;
		sa.sa_handler = handle_signal;

        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
		while (1)
		{
			prompt = create_prompt();
			line_read = readline(prompt);
			if (!line_read)
				return (0);
			free(prompt);
			if (ft_strlen(line_read) == 0)
				continue ;
			add_history(line_read);
			line = (t_mini){0};
			validating(line_read, &line);
			expansion(&line, &data);
			p_count(&line);
			token = malloc(sizeof(t_tokens) * (line.pipe_num));
			if (!token)
				malloc_failure();
			function(&line, token);
			execute(token, &data, &line);
			free(line_read);
			free_2d(line.metaed);
			free_2d(token->command);
			free(token);
		}
	}
	return (0);
}
