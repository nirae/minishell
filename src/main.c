/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/07 19:06:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n%s", PROMPT);
	}
}

void	catch_signal_kill(int signal)
{
	if (signal == SIGINT)
	{
		kill(g_pid, SIGTERM);
	}
}

// void	catch_signal_echo(int signal)
// {
// 	if (signal == SIGINT)
// 	{
//
// 	}
// }

void	error()
{
	ft_printf("minishell failed\n");
	exit(EXIT_FAILURE);
}

/////////////////////////////////////////////////////////////////////////////
///////////////////////// ECHO ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// static int		echo(char *str)
// {
// 	int i = -1;
// 	int y = 0;
// 	char *tmp;
// 	char final_str[4096];
// 	int nb_double_quotes = 0;
// 	int nb_simple_quotes = 0;
// // 1 simple
// // 2 double
// 	int first_quote = 0;
// 	char *line;
//
// 	//signal(SIGINT, catch_signal_echo);
// 	final_str[0] = 0;
// 	while (str[++i])
// 	{
// 		//ft_printf("char: %c, nb double quotes: %d, nb simple quotes: %d, first_quote: %d\n", str[i], nb_double_quotes, nb_simple_quotes, first_quote);
// 		signal(SIGINT, catch_signal);
// 		if (str[i] == ' ' && (nb_double_quotes % 2) == 0 && (nb_simple_quotes % 2) == 0)
// 			continue;
// 		else if (str[i] == '\"')
// 		{
// 			if (first_quote == 1 && (nb_simple_quotes % 2) != 0)
// 			{
// 				final_str[y] = str[i];
// 				y++;
// 				// if (str[i + 1] == ' ')
// 				// {
// 				// 	final_str[y] = ' ';
// 				// 	y++;
// 				// }
// 			}
// 			nb_double_quotes++;
// 			if ((nb_simple_quotes % 2) == 0)
// 				first_quote = 2;
// 			//continue;
// 		}
// 		else if (str[i] == '\'')
// 		{
// 			if (first_quote == 2 && (nb_double_quotes % 2) != 0)
// 			{
// 				final_str[y] = str[i];
// 				y++;
// 				// if (str[i + 1] == ' ')
// 				// {
// 				// 	final_str[y] = ' ';
// 				// 	y++;
// 				// }
// 			}
// 			nb_simple_quotes++;
// 			if ((nb_double_quotes % 2) == 0)
// 				first_quote = 1;
// 		//	continue;
// 		}
// 		else
// 		{
// 			final_str[y] = str[i];
// 			y++;
// 			if (str[i + 1] == ' ')
// 			{
// 				final_str[y] = ' ';
// 				y++;
// 			}
// 		}
// 		if (str[i + 1] == 0)
// 		{
// 			if (((nb_double_quotes % 2) != 0 && first_quote == 2) || ((nb_simple_quotes % 2) != 0 && first_quote == 1))
// 			{
// 				ft_printf("termine ta quote putain>");
// 				line = NULL;
// 				if (get_next_line(0, &line) < 0)
// 					error();
// 				if (!line[0])
// 					line[0] = '\n';
// 				tmp = str;
// 				str = ft_strjoin(tmp, "\n");
// 				tmp = str;
// 				str = ft_strjoin(tmp, line);
// 				ft_strdel(&line);
// 			}
// 		}
// 		//ft_printf("char: %c, nb double quotes: %d, nb simple quotes: %d, first_quote: %d\n", str[i], nb_double_quotes, nb_simple_quotes, first_quote);
// 	}
// 	final_str[y] = '\0';
// 	if (final_str[0])
// 		ft_printf("%s", final_str);
// 	exit(0);
// }

/////////////////////////////////////////////////////////////////////////////
///////////////////////// END ECHO ////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*
**	Return the complete path of a file name or exit if malloc failed
*/

static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (name[0] == '/' || name[0] == '.')
		return (name);
	if (parent[ft_strlen(parent) - 1] == '/')
	{
		if (!(tmp = ft_strdup(parent)))
			error();
	}
	else
	{
		if (!(tmp = ft_strjoin(parent, "/")))
			error();
	}
	if (!(result = ft_strjoin(tmp, name)))
		error();
	ft_strdel(&tmp);
	return (result);
}

////////////////////////////////////////////////////////////////////////////////
								//PARSING
////////////////////////////////////////////////////////////////////////////////

char		**ft_strsplit_parser2(char *str)
{
	int		i;
	int		j;
	int		y;
	char	**result;
	char	*line;
	char	*tmp;


	if (str == NULL)
		return (NULL);
	if (!(result = ft_memalloc(100000000)))
		return (0);
	i = -1;
	j = 0;
	while (str[++i])
	{
		//signal(SIGINT, catch_signal);
		if (!(result[j] = ft_strnew(10000)))
			return (0);
		if (str[i] == ' ' || str[i] == '\t')
			continue;
		else if (str[i] == '\"')
		{
			// if (!(result[j] = ft_strnew(10000)))
			// 	return (0);
			y = 0;
			while (str[i++])
			{
				if (str[i] == '\"')
				{
					//j++;
					break;
				}
				result[j][y] = str[i];
				y++;
				if (str[i + 1] == 0)
				{
					ft_printf("termine ta quote putain>");
					line = NULL;
					if (read_prompt(0, &line) < 0)
						error();
					if (!line[0])
						line[0] = '\n';
					tmp = str;
					str = ft_strjoin(tmp, "\n");
					tmp = str;
					str = ft_strjoin(tmp, line);
					ft_strdel(&line);
					continue;
				}
			}
		}
		else if (str[i] == '\'')
		{
			// if (!(result[j] = ft_strnew(10000)))
			// 	return (0);
			y = 0;
			while (str[i++])
			{
				if (str[i] == '\'')
				{
					//j++;
					break;
				}
				result[j][y] = str[i];
				y++;
				if (str[i + 1] == 0)
				{
					ft_printf("termine ta quote putain> ");
					line = NULL;
					if (read_prompt(0, &line) < 0)
						error();
					if (!line[0])
						line[0] = '\n';
					tmp = str;
					str = ft_strjoin(tmp, "\n");
					tmp = str;
					str = ft_strjoin(tmp, line);
					ft_strdel(&line);
					continue;
				}
			}
		}
		// if (!(result[j] = ft_strnew(10000)))
		// 	return (0);
		y = 0;
		while (str[i] != ' ' && str[i] != '\t' && str[i] && str[i] != '\"' && str[i] != '\'')
		{
			result[j][y] = str[i];
			y++;
			i++;
		}
		j++;
	}
	return (result);
}

// int		minishell_parser(char *input, char ****command)
// {
// 	int		i;
// 	char	**commands;
//
// 	*command = ft_memalloc((ft_strlen(input) + 1) * 8);
//
// 	if (input[0] == 0)
// 		return (FALSE);
// 	if (!(commands = ft_strsplit(input, ';')))
// 		return (FALSE);
// 	i = -1;
// 	while (commands[++i])
// 	{
// 		// if (!((*command)[i] = ft_strsplit(commands[i], ' ')))
// 		if (!((*command)[i] = ft_strsplit_parser2(commands[i])))
// 			return (FALSE);
// 	}
// 	(*command)[i] = NULL;
//
// 	// // DEBUG //
// 	// i = -1;
// 	// int y;
// 	// ft_printf("DEBUG:\n");
// 	// while (commands[++i])
// 	// {
// 	// 	y = -1;
// 	// 	while ((*command)[i][++y])
// 	// 	{
// 	// 		ft_printf("commande %d = %s\n", y, (*command)[i][y]);
// 	// 	}
// 	// }
// 	// // FIN DEBUG //
//
// 	// if (!(*command = ft_strsplit(input, ' ')))
// 	// 	return (0);
// 	return (1);
// }

////////////////////////////////////////////////////////////////////////////////
								//FIN PARSING
////////////////////////////////////////////////////////////////////////////////

/*
**	A proteger!!!!!!
*/

/*char		**get_my_env(char **environ)
{
	int		i;
	char	**my_env = NULL;

	i = -1;
	while (environ[++i]);
	my_env = ft_memalloc((i + 1) * sizeof(char *));
	i = -1;
	while (environ[++i])
		my_env[i] = ft_strdup(environ[i]);
	my_env[i] = NULL;
	return (my_env);
}*/

t_varenv	*create_varenv(char *name, char *content)
{
	t_varenv	*varenv;

	// Gerer l'erreur
	if (!(varenv = ft_memalloc(sizeof(t_varenv *) + (sizeof(char *) * 2))))
		error();
	if (!(varenv->name = ft_strdup(name)))
		error();
	if (!content)
		varenv->content = NULL;
	else if (!(varenv->content = ft_strdup(content)))
		error();
	return (varenv);
}

void		create_my_env(t_list **lst, char **environ)
{
	int		i;
	t_list	*tmplst;
	char	**env;
	int		pos;

	if (environ[0] == NULL)
	{
		if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
			ft_printf("lstnew a foire\n");
		tmplst->content = create_varenv("SHELL", "minishell");
		*lst = tmplst;
		return;
	}
	i = 0;
	while (environ[i])
	{
		// a proteger
		if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
			ft_printf("lstnew a foire\n");
		if (!(env = ft_strsplit(environ[i], '=')))
		 	ft_printf("strsplit a foire\n");
		pos = ft_strpos(environ[i], '=');
		// tmplst->content = create_varenv(env[0], env[1]);
		tmplst->content = create_varenv(env[0], &environ[i][pos + 1]);
		if (!(*lst))
			*lst = tmplst;
		else
			ft_lstadd(lst, tmplst);
		ft_memdel((void **)&env);
		i++;
	}
}

void		env_lst_to_tab(t_list **lst, char ***tab)
{
	int		i;
	char	*tmp;
	t_list	*node;

	if (*tab != NULL)
	{
		i = 0;
		while((*tab)[i++])
			ft_strdel(&(*tab)[i]);
		*tab = NULL;
	}
	node = *lst;
	if (*tab == NULL)
		if (!(*tab = (char **)ft_memalloc(sizeof(char *) * (ft_lstlen(*lst) + 1))))
			return;
	if (node != NULL)
	{
		i = 0;
		while (node)
		{
			if (!((*tab)[i] = ft_strjoin(((t_varenv *)((node)->content))->name, "=")))
				ft_printf("strjoin fail\n");
			if (((t_varenv *)((node)->content))->content)
			{
				tmp = (*tab)[i];
				if (!((*tab)[i] = ft_strjoin((*tab)[i], ((t_varenv *)((node)->content))->content)))
					ft_printf("strjoin fail\n");
				ft_strdel(&tmp);
			}
			(node) = (node)->next;
			i++;
		}
		(*tab)[i] = NULL;
	}
}

char		**get_env_paths(t_list *lst)
{
	t_list	*tmp;
	char	**env_paths;

	tmp = lst;
	while (lst)
	{
		if (ft_strcmp((((t_varenv *)(tmp->content))->name), "PATH") == 0)
			break;
		if (tmp->next == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	env_paths = ft_strsplit(((t_varenv *)(tmp->content))->content, ':');
	return (env_paths);
}

int			change_env_var(t_list **lst, char *name, char *newcontent)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp((((t_varenv *)((tmp)->content))->name), name) == 0)
			break;
		if ((tmp)->next == NULL)
			return (FALSE);
		(tmp) = (tmp)->next;
	}
	((t_varenv *)((tmp)->content))->content = newcontent;
	return (TRUE);
}

void		del_lst(void *content, size_t size)
{
	(void)size;
	ft_strdel(&((t_varenv *)(content))->name);
	ft_strdel(&((t_varenv *)(content))->content);
}

int			remove_one(t_list **lst, char *name)
{
	t_list	*prev;
	t_list	*tmp;


	tmp = *lst;
	if (tmp && ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
	{
		prev = tmp;
		*lst = tmp->next;
		ft_lstdelone(&prev, del_lst);
		return (1);
	}
	while(tmp)
	{
		if (tmp->next && ft_strcmp(((t_varenv *)(tmp->next->content))->name, name) == 0)
		{
				prev = tmp->next;
				tmp->next = tmp->next->next;
				ft_lstdelone(&prev, del_lst);
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

// t_varenv		*get_env_var_by_name(char *name)
// {
// 	t_list	*tmp;
//
//
// 	tmp = g_env_lst;
// 	while(tmp)
// 	{
// 		if (ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
// 			return (((t_varenv *)(tmp->content)));
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

void		print_lstenv(t_list *lst)
{
	ft_printf("%s=%s\n", ((t_varenv *)(lst->content))->name, ((t_varenv *)(lst->content))->content);
}

// int			hachage(char *str)
// {
// 	int		i;
// 	int		result;
//
// 	i = -1;
// 	result = 0;
// 	while (str[++i])
// 		result += str[i];
// 	result %= 100;
// 	return (result);
// }
//
// void		init_hash_tab(t_varenv **tab[HASH_TAB_MAX])
// {
// 	int i;
//
// 	i = -1;
// 	while (*tab[++i])
// 		*tab[i] = NULL;
// }
//
// void		add_hash_tab(t_varenv **tab[HASH_TAB_MAX], char *var)
// {
// 	char	**split;
//
// 	if (!(split = ft_strsplit(var, '=')))
// 		ft_printf("strsplit a foire\n");
// 	*tab[hachage(split[0])] = create_varenv(split[0], split[1]);
// }



int			main(int ac, char **av, char **environ)
{
//	pid_t	father;
	char	*strrr;
	char	***command = NULL;
	char	**env_paths;
	//t_list	*env;
	t_list	*tmplst;
	struct stat st;
	int		i;
	int		y;
	int		status;
//	int 	y;
	char 	str[PATH_MAX + 1];

	// t_varenv	*hash_tab[HASH_TAB_MAX];
	//
	// init_hash_tab(&hash_tab);


	(void)ac;
	(void)av;
	g_env_lst = NULL;
	g_env_tab = NULL;
	// copie de environ
	create_my_env(&g_env_lst, environ);
	//ft_lstiter(env, print_lstenv);
	env_paths = get_env_paths(g_env_lst);
	env_lst_to_tab(&g_env_lst, &g_env_tab);
	/*
	** Boucle infinie du programme
	*/
	while (666)
	{
		// Surveille le signal de CTRL C
		signal(SIGINT, catch_signal);
		// Affiche le prompt
		ft_printf("\n%s", PROMPT);
		// Lis l'entree standard
		// line = NULL;
		// if (get_next_line(0, &line) < 0)
		// if (read_prompt(0, &line) < 0)
		// 	error();
		get_complete_command(&strrr);
		//ft_printf("commande = %s\n", strrr);
		/*
		**	PARSING
		*/
		if (!(minishell_parser(strrr, &command)))
		{
			ft_printf("%s\n", "Le parsing a fail");
			continue;
		}
		// ft_strdel(&line);
		// read_prompt(0, &line, 1);
		// ft_printf("reste du buffer : %s\n", line);
	 	// ft_strdel(&line);
		y = -1;
		while (command[++y])
		{
			if (command[y][0] == NULL)
				continue;
			/*
			**	GESTION DES BULTINS
			*/
			if (ft_strcmp(command[y][0], "exit") == 0)
			{
				ft_printf("c'est ca degage\n");
				if (command[y][1])
					exit(ft_atoi(command[y][1]));
				else
					exit(EXIT_SUCCESS);
			}
			else if (ft_strcmp(command[y][0], "mypwd") == 0)
			{
				getcwd(str, PATH_MAX + 1);
				ft_printf("pwd : %s\n", str);
				continue;
			}
			else if (ft_strcmp(command[y][0], "cd") == 0)
			{
				char 	oldpwd[PATH_MAX + 1];
				// recupere le pwd
				getcwd(oldpwd, PATH_MAX + 1);
				if ((chdir(command[y][1])) < 0)
					ft_printf("chdir failed\n");
				else
				{
					if (!(change_env_var(&g_env_lst, "OLDPWD", oldpwd)))
						ft_printf("OLDPWD not found\n");
					// PWD
					char 	pwd[PATH_MAX + 1];
					// recupere le pwd
					getcwd(pwd, PATH_MAX + 1);
					if (!(change_env_var(&g_env_lst, "PWD", pwd)))
						ft_printf("PWD not found\n");
					ft_printf("... moving to %s ....\n", command[y][1]);
				}
				continue;
			}
			else if (ft_strcmp(command[y][0], "env") == 0)
			{
				//ft_lstiter(g_env_lst, print_lstenv);
				int i = 0;
				while (g_env_tab[i])
				{
					ft_printf("%s\n", g_env_tab[i]);
					i++;
				}
				continue;
			}
			else if (ft_strcmp(command[y][0], "setenv") == 0)
			{
				if (command[y][1])
				{
					tmplst = ft_lstnew(NULL, sizeof(t_varenv *));
					tmplst->content = create_varenv(command[y][1], command[y][2]);
					ft_lstaddend(&g_env_lst, tmplst);
					env_lst_to_tab(&g_env_lst, &g_env_tab);
					env_paths = get_env_paths(g_env_lst);
				}
				continue;
			}
			else if (ft_strcmp(command[y][0], "unsetenv") == 0)
			{
				remove_one(&g_env_lst, command[y][1]);
				env_lst_to_tab(&g_env_lst, &g_env_tab);
				env_paths = get_env_paths(g_env_lst);
				continue;
			}
			else if (ft_strcmp(command[y][0], "echo") == 0)
			{
				int z = 0;
				while (command[y][1 + z])
				{
					ft_printf("%s", command[y][1 + z]);
					z++;
					if (command[y][1 + z])
						ft_printf(" ");
				}
				// if (command[y][1])
				// {
				// 	g_pid = fork();
				// 	if (g_pid == 0)
				// 	{
				// 		echo(&line[4]);
				// 		//kill(g_pid, SIGTERM);
				// 	}
				// 	else if (g_pid < 0)
				// 		ft_printf("fail\n");
				// 	else if (g_pid > 0)
				// 	{
				// 		signal(SIGINT, catch_signal_kill);
				// 		waitpid(g_pid, &status, 0);
				// 	}
				// 	//echo(&line[4]);
				//}
				ft_printf("\n");
				continue;
			}
			/*
			**	FIN DES BUILTINS
			*/
			// Recherche du fichier dans les repos du path
			i = -1;
			if (!env_paths)
			{
				ft_printf("pas de variable PATH");
				continue;
			}
			while (env_paths[++i])
			{
				// Si le fichier existe pas dans ce path, continue a boucler
				if ((lstat(get_complete_path(env_paths[i], command[y][0]), &st)) < 0)
				{
					// Si c'etait le dernier -> pas trouve
					if (!env_paths[i + 1])
					{
						ft_printf("minishell: command not found: %s\n", command[y][0]);
						break;
					}
					continue;
				}
				// Si le fichier est trouvé on l'execute
				else
				{
					ft_printf("tiens ton resultat de merde :\n");
					g_pid = fork();
					if (g_pid == 0)
					{
						execve(get_complete_path(env_paths[i], command[y][0]), command[y], g_env_tab);
						//kill(g_pid, SIGTERM);
					}
					else if (g_pid < 0)
						ft_printf("fail\n");
					else if (g_pid > 0)
					{
						signal(SIGINT, catch_signal_kill);
						waitpid(g_pid, &status, 0);
					}
					break;
				}
			}
		}
		//ft_printf("tiens ton resultat de merde : %s\n", line);

	}
	return (0);
}
