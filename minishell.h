/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/24 11:47:19 by tparratt         ###   ########.fr       */
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

typedef struct s_data
{
	char	**envp;
	int		err_num;
}				t_data;

char		*get_path(char **tokens, char **envp);
void		free_2d(char **tab);
void		print_2d(char **tab);
char		*join_and_free(char *prompt, char *str);
int			contains_pipe(char *line_read);
extern void	rl_replace_line(const char *text, int clear_undo);
void		execute_pipe(t_cmd *cmds, char **argc);
void		echo(char **args);
void		pwd(void);
void		cd(char **args, t_data *data);
void		env(char **args, t_data *data);
void		exit_cmd(char **args, t_data *data);
void		export_cmd(char **args, t_data *data);
void		export(char *arg, t_data *data);
void		unset_cmd(char **args, t_data *data);
void		unset(char *arg, t_data *data);
char		*ft_getenv(char **envp, char *str);
void		handle_signal(int signal);
void		set_term_attr(void);
void		check_tokens(char **tokens, t_data *data, char *line_read);
char		**execute(char *line_read, char **tokens, char **envp);
char		**malloc_envp(char **envp);
char		**envp_dup(char **envp);
void		malloc_failure(void);

#endif
