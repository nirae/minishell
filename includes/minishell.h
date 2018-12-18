/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:46:49 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 04:25:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "libftprintf.h"

# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>
#include "errno.h"

# define PROMPT "minishell $> "
# define PROMPT_READ "$>"
/*
**	Pour my_errno
*/

# define FAIL_MALLOC	100

# define HASH_TAB_MAX	4096
# define TRUE			1
# define FALSE			0
# define FAIL_			3

# define SIMPLE_QUOTE 	45
# define DOUBLE_QUOTE 	46

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


int			exec_command(char **command, char **env);
int					read_prompt(const int fd, char **line);
int					get_complete_command(char **str);
// char 				**ft_split_escape(char *str, char sep);

/*
**	PARSING
*/

int					minishell_parser(char *input, char ****command);
char				**minishell_split(char *str);

//char		**ft_split_escape(char *str, char sep);
int					ft_count_words_escape(char *str, char sep);
int 	ft_count_letters_escape(char *str, char sep);
char		**ft_strsplit_with_escape(char *str, char sep);

/*
**		BUILTINS
*/

int 	echo_builtin(char **args);
int		is_valid_option(char c, char *options);
void	options_parser(char **args, int *options, int *pos_args,
			int (*set_options)(char *, int *, int));

int 	env_builtin(char **args);
void		exit_builtin(char *arg);

/*
**	CD
*/

int		ft_realloc_addend_tab(char ***tab, char *elem);
char	*ft_strjointab(char **tab, char sep);
int		ft_stringtab_len(char **tab);
int		check_path_errors(char *path);
char	*get_final_path(char *path);
int	build_pwd_tab(char ***arg_tab, char ***pwd_tab, int pwd_tab_len);
int		cd_builtin(char **args);

/*
**	ENVIRONMENT
*/
void		env_lst_to_tab(t_list **lst, char ***tab);
int		add_env_var(t_list **lst, char *name, char *content);
t_varenv	*create_varenv(char *name, char *content);
void		del_env_var(void *content, size_t size);
int			change_env_var(t_list **lst, char *name, char *newcontent);
t_varenv		*get_env_var_by_name(char *name);

int		ft_strarraylen(char **tab);
void	ft_strtabdel(char ***tab);
void	error(void);

#endif
