/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:46:49 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/26 22:45:41 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "libftprintf.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>

# define PROMPT "minishell $> "

# define FAIL_MALLOC	100

# define TRUE			1
# define FALSE			0

# define OPTIONS_CD		"LP"
# define OPTIONS_ENV	"i"
# define OPTIONS_ECHO	"n"
# define OPT_L 			(1 << 27)
# define OPT_P 			(1 << 28)
# define OPT_I			(1 << ('i' - 'a'))
# define OPT_N			(1 << ('n' - 'a'))

pid_t				g_pid;
t_list				*g_env_lst;
char				**g_env_tab;
int					g_my_errno;

typedef struct		s_command
{
	char			*path;
	char			**args;
}					t_command;

typedef struct		s_varenv
{
	char			*name;
	char			*content;
}					t_varenv;

int					exec_command(char **command, char **env);
char				*get_path_of_bin(char *path);
int					read_prompt(const int fd, char **line);
int					get_complete_command(char **str);
void				*cmd_not_found(char *str);
void				*perm_denied(char *str);
int					replace_dollar(char **final_str, int *i);
/*
**	PARSING
*/

int					minishell_parser(char *input, char ****command);
char				**ft_strsplit_whitespace(char const *s);

/*
**		BUILTINS
*/

int					unsetenv_builtin(char **args);
int					manage_builtins(char **command, char ****commands);
int					echo_builtin(char **args);
int					is_valid_option(char c, char *options);
void				options_parser(char **args, int *options, int *pos_args,
						int (*set_options)(char *, int *, int));
int					env_builtin(char **args);
int					setenv_builtin(char **args);
void				exit_builtin(char *arg, char ****commands);

/*
**	ENV
*/

t_list				*ft_lstcpy(t_list *src, t_list **dest);
int					manage_envvar_args(int options, t_list **env_lst_cpy,
						char **args, int *pos_args);

/*
**	CD
*/

char				*get_pwd_for_cd(int pos_args, char **args);
int					ft_realloc_addend_tab(char ***tab, char *elem);
char				*ft_strjointab(char **tab, char sep);
int					ft_stringtab_len(char **tab);
int					check_path_errors(char *path);
char				*get_final_path(char **path);
int					build_pwd_tab(char ***arg_tab, char ***pwd_tab,
						int pwd_tab_len);
int					cd_builtin(char **args);

/*
**	ENVIRONMENT
*/

int					remove_env_var(t_list **lst, char *name);
int					env_lst_to_tab(t_list **lst, char ***tab);
int					env_tab_to_lst(t_list **lst, char **environ);
int					add_env_var(t_list **lst, char *name, char *content);
t_varenv			*create_varenv(char *name, char *content);
void				del_env_var(void *content, size_t size);
int					change_env_var(t_list **lst, char *name, char *newcontent);
t_varenv			*get_env_var_by_name(char *name);

int					ft_strarraylen(char **tab);
void				ft_strtabdel(char ***tab);
void				error(void);

#endif
