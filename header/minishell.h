/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:20:34 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/17 17:31:28 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ARG 0
# define CMD 1
# define DELIM 2
# define DELIM_TAB 3
# define REDIR 4
# define PIPE 5
# define INPUT 6
# define APPEND 7
# define MAX_CH 4096

typedef struct s_prog
{
	char	**env;
	char	**token;
	int		*type;
	int		ret;
	int		pipes;
	int		*pipfd;
	int		pipnum;
	int		fdin;
	int		fdout;
	int		in;
	int		out;
	int		exec;
	int		redinput;
	int		redoutput;
	int		parent;
	int		delim;
	int		err;
}	t_prog;

typedef struct s_pid
{
	int	*pid;
	int	*status;
	int	size;
	int	index;
	int	in;
	int	out;
	int	fd;
	int	pipsize;
	int	*pipfd;
}	t_pid;

int		exec_cmd(t_prog *prog, char **cmd);
void	sig_int(int sig);
void	sig_quit(int sig);
void	interrupt_delim(int sig);
char	**sort_env(char **env);
int		skip_notsep(char *line, int *i);
int		parseline(t_prog *prog);
void	get_token(char *line, t_prog *prog);
void	skip_space(char *line, int *i);
void	free_split(char **strs);
int		no_backslash(char c, char behind);
void	cnt_notsep(char *line, int i, int *cnt);
int		check_quotes(char *line);
char	*get_env(char *env, t_prog *prog);
void	redir_output(t_prog *prog, char *file, int type);
void	redir_input(t_prog *prog, char *file);
void	redir_delim(t_prog *prog, char *delim, int index);
void	pipe_init(t_prog *prog);
void	parse_exec(t_prog *prog, int i);
int		get_type(t_prog *prog, int index);
int		is_builtin(char *cmd);
void	builtin_exec(t_prog *prog, char **cmd);
void	expand(char **cmd, t_prog *prog);
char	**parse_cmd(t_prog *prog, int i);
int		check_token(t_prog *prog);
char	*find_env(char *str, t_prog *prog, int i);
int		check_type(t_prog *prog, int index, char *types);
void	echo_cmd(t_prog *prog, char **cmd);
void	ft_pwd(t_prog *prog);
int		pipe_size(t_prog *prog);
void	close_pipes(t_prog *prog);
void	builtin_pipe(t_prog *prog);
void	pipe_exec(t_prog *prog, char *path, char **cmd);
void	close_piptmp(t_prog *prog);
void	reset_fd(t_prog *prog);
void	builtin_chk(t_prog *prog, char **cmd);
void	print_error_c(t_prog *prog, char *str);
void	dup_delim(int fd);
void	loop_delim(t_prog *prog, char *delim, int fd, int z);
int		next_pipe(t_prog *prog, int i);
int		next_op(t_prog *prog, int i);
int		check_hyphen(char *line, int i);
char	*remove_tabs(char *line);
void	redir(t_prog *prog, int z);
int		ft_strcmp_lu(char *s1, char *s2);
void	ft_exit(t_prog *prog, char **cmd);
void	ft_env(t_prog *prog);
int		ft_env_size(char **env);
void	ft_cd(t_prog *prog, char **env, char **cmd);
char	*ft_get_pwd(t_prog *prog);
void	ft_export(t_prog *prog, char **cmd);
void	ft_unset(t_prog *prog, char **cmd);
int		ft_find_env(char **env, char *str);
int		ft_searh_index(char *str, char c);
char	**ft_distr_export(t_prog *prog, char **env);
void	ft_print_export(char **env);
void	ft_add_new_env(t_prog *prog, char *str);
void	ft_check_env(t_prog *prog, char **env);
void	fix_type(t_prog *prog);
int		is_redir(t_prog *prog, int i);
int		cnt_fix(t_prog *prog, int i);
void	swap_tokens(t_prog *prog, int i);
void	fix_token(t_prog *prog);
int		dollar_am(char *str);
void	ft_check_env(t_prog *prog, char **env);
char	**cpy_env(char **env);
void	do_env(char *str, int i, t_prog *prog, char **ret);
char	*env_name(char *str, int i, int len);
int		env_len(char *str, int i);
void	set_default(t_prog *prog);
void	print_error_d(char *str);
void	fix_global(t_prog *prog);
void	remove_quotes(char **cmd);
void	fandr_quotes(char **str);
char	**remove_cmd(char **cmd, int pos);
char	*quotes_extra(char *str);
void	close_pip(t_prog *prog);
void	readline_fix(t_prog *prog, int i);
void	find_quote(char *str, int *i, int *chk);
int		cnt_noquotes(char *str);
void	close_std(t_prog *prog, int fd);
void	weird_close(void);

extern t_pid	g_pid;

#endif