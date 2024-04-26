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
		perror("execve failure");
		exit(1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
		execve(cmds->path2, cmds->cmd2, envp);
		perror("execve failure");
		exit(1);
	}
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

