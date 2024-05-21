/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/21 16:12:57 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>
# include <string.h>
# include <errno.h>

typedef struct s_cmd
{
	char	**cmd1;
	char	*path1;
	char	**cmd2;
	char	*path2;
}				t_cmd;

char		*get_path(char **tokens, char **envp);
void		free_2d(char **tab);
void		print_2d(char **tab);
char		*join_and_free(char *prompt, char *str);
int			contains_pipe(char *line_read);
extern void	rl_replace_line(const char *text, int clear_undo);
void		execute_pipe(t_cmd *cmds, char **argc);
void		echo(char **args);
void		pwd(void);
char		**cd(char **args, char **envp);
void		env(char **args, char **envp);
void		exit_cmd(char **args);
char		**export_cmd(char **args, char **envp);
char		**export(char *arg, char **envp);
char		**unset_cmd(char **args, char **envp);
char		**unset(char *arg, char **envp);
char		*ft_getenv(char **envp, char *str);
void		handle_signal(int signal);
void		set_term_attr(void);
char		**check_tokens(char **tokens, char **envp, char *line_read);
char		**execute(char *line_read, char **tokens, char **envp);
char		**malloc_envp(char **envp);
char		**envp_dup(char **envp);
void		print_error_message(char **args);

#endif
