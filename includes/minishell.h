/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:46:49 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/15 00:22:02 by ndubouil         ###   ########.fr       */
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

# define PROMPT "tape ta commande connard > "

# define HASH_TAB_MAX	4096
# define TRUE			1
# define FALSE			0
# define FAIL_MALLOC	2
# define FAIL_ 			3

# define SIMPLE_QUOTE 	45
# define DOUBLE_QUOTE 	46

# define OPTIONS_CD		"LP"
# define OPT_L 			(1 << 27)
# define OPT_P 			(1 << 28)

pid_t				g_pid;
t_list				*g_env_lst;
char				**g_env_tab;
//int					my_errno;

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
**	BUILTINS
*/

void		exit_builtin(char *arg);
int		cd_builtin(char **args);

/*
**	ENVIRONMENT
*/

int		add_env_var(char *name, char *content);
t_varenv	*create_varenv(char *name, char *content);
void		del_env_var(void *content, size_t size);
int			change_env_var(t_list **lst, char *name, char *newcontent);
t_varenv		*get_env_var_by_name(char *name);

void	error(void);

#endif
