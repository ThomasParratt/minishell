/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:16:35 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/10 14:09:15 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (args[i + 1] == NULL)
			ft_printf("%s", args[i]);
		else
			ft_printf("%s ", args[i]);
		i++;
	}
}

void	pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd command failure");
		exit(1);
	}
	ft_printf("%s\n", cwd);
}

void	env(char **envp)
{
	print_2d(envp);
}

void	exit_cmd(void)
{
	ft_printf("exit\n");
	exit(0);
}

char	**check_builtins(char **tokens, char **envp, char *line_read)
{
	//static int	allocated;

	if (!ft_strncmp(tokens[0], "echo", 4) && !ft_strncmp(tokens[1], "-n", 3))
		echo(tokens);
	else if (!ft_strncmp(tokens[0], "pwd", 3))
		pwd();
	else if (!ft_strncmp(tokens[0], "cd", 2))
		envp = cd(tokens, envp);
	else if (!ft_strncmp(tokens[0], "env", 3))
		env(envp);
	else if (!ft_strncmp(tokens[0], "exit", 4))
		exit_cmd();
	else if (!ft_strncmp(tokens[0], "export", 6))
		envp = export(tokens[1], envp);
	else if (!ft_strncmp(tokens[0], "unset", 5))
		envp = unset(tokens[1], envp);
	else
		execute(line_read, tokens, envp);
	return (envp);
}

