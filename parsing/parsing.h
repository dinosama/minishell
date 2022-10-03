/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaapatou <aaapatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:53:56 by aaapatou          #+#    #+#             */
/*   Updated: 2022/01/30 12:46:32 by aaapatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define _DEFAULT_SOURCE
# include <sys/types.h>
# include <signal.h>
# include "../minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

extern int	g_return;

typedef struct s_checkerror
{
	int			i;
	int			iq;
	int			cp;
	int			cti;
	int			cto;
}				t_checkerror;

// CHECK
int		ft_whitespace(char c);
int		is_pipe(char c);
int		quote_check(char c, int in_quote);
int		quote_in_word(char *str, int i);
// INIT
char	**copy_env(char **env);
void	init_command(t_cmd *cmd, char ***env, int exit);
void	check_init(t_checkerror *error);
// PARSE
char	*get_word(char *str, int *len, t_cmd *act);
void	get_pipe(char *line, int *i, t_cmd *act);
void	take_command(char *line, int *i, t_cmd *act);
t_cmd	*get_line(char *line, char ***env, int exit);
int		read_line(char ***env, struct sigaction *sa1, struct sigaction *sa2);
// HEREDOC
char	*get_heredoc(char *line, int *i, t_cmd *act, int fail);
void	show_error_heredoc(int s_line, char *delimiter);
// REDIRECTIONS
int		is_redirect(char c);
void	clean_redir(t_cmd *act, int redirect);
int		wich_redirect(char *line, int *i);
t_redir	*create_redirect(char *line, int *i, int type, t_cmd *act);
int		get_redirect(char *line, int *i, t_cmd *act);
t_redir	*show_error_redir(char *line, int *i, t_cmd *act, t_redir *redir);
// SIGNALS
void	manage_sig(int interactive, struct sigaction *s1, struct sigaction *s2);
void	handle_sig(int sig);
void	handle_sig_two(int sig);
void	handle_sig_heredoc(int sig);
// ERROR
t_cmd	*check_error(char *line, t_cmd *tokens);
int		go_to_pipe(char *line, int *i, t_cmd *cmd);
// ENV
char	*replace_with_env(char *word, int *i, t_cmd *act, int in_quote);
char	*get_env_variable(char *word, t_cmd *act, int heredoc);
// TEST
void	show_red(t_cmd *tokens);
void	show_tokens(t_cmd *tokens);
// UTILS
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		calcul_arg(char *line, int i);
char	*ft_substr(char *s, int start, int len);
char	*delete_quotes(char *word);
char	*get_prompt(char **env);
char	*reading(char *line, char ***env);
int		start_command(char *line, int *i, t_cmd *act);
void	get_pipe(char *line, int *i, t_cmd *act);
t_cmd	*get_first_cmd(t_cmd *cmd);
t_cmd	*get_last_cmd(t_cmd *act);
t_cmd	*create_cmd_malloc(char ***env, int exit);

#endif
