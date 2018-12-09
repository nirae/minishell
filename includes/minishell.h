/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:46:49 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/09 20:45:19 by ndubouil         ###   ########.fr       */
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

# define PROMPT "tape ta commande connard > "

# define HASH_TAB_MAX	4096
# define TRUE			1
# define FALSE			0
# define FAIL_MALLOC	2
# define FAIL_ 			3


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
char 				**ft_split_escape(char *str, char sep);

/*
**	PARSING
*/

int					minishell_parser(char *input, char ****command);
char				**minishell_split(char *str);


/*
**	ENVIRONMENT
*/

t_varenv		*get_env_var_by_name(char *name);

#endif
