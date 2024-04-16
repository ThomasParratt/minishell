#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void	execute_pipe(char **cmd1, char **cmd2, char **envp)
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
		execve(cmd1[0], cmd1, envp);
		perror("execve");
		exit(1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
		execve(cmd2[0], cmd2, envp);
		perror("execve");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 3)
		return (1);
	char	*cmd1[] = {argv[1], NULL}; //this would contain arguments if there are any
	char	*cmd2[] = {argv[2], NULL}; //this would contain arguments if there are any

	execute_pipe(cmd1, cmd2, envp);
	return (0);
}

