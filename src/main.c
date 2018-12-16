/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/17 00:09:28 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void     ft_getleaks(char *str)
// {
//        system("leaks minishell");
//        ft_printf("%s\n", str);
//        getchar();
// }

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

/*
**	Return the complete path of a file name or exit if malloc failed
*/

static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (name[0] == '/' || name[0] == '.')
		return (name);
	if (parent == NULL)
	{
		if (!(result = ft_strjoin("./", name)))
			error();
		return (result);
	}
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
		ft_strtabdel(&env);
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

// int			change_env_var(t_list **lst, char *name, char *newcontent)
// {
// 	t_list	*tmp;
//
// 	tmp = *lst;
// 	while (tmp)
// 	{
// 		if (ft_strcmp((((t_varenv *)((tmp)->content))->name), name) == 0)
// 			break;
// 		if ((tmp)->next == NULL)
// 			return (FALSE);
// 		(tmp) = (tmp)->next;
// 	}
// 	((t_varenv *)((tmp)->content))->content = newcontent;
// 	return (TRUE);
// }
//
// void		del_lst(void *content, size_t size)
// {
// 	(void)size;
// 	ft_strdel(&((t_varenv *)(content))->name);
// 	ft_strdel(&((t_varenv *)(content))->content);
// }

int			remove_one(t_list **lst, char *name)
{
	t_list	*prev;
	t_list	*tmp;


	tmp = *lst;
	if (tmp && ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
	{
		prev = tmp;
		*lst = tmp->next;
		ft_lstdelone(&prev, del_env_var);
		return (1);
	}
	while(tmp)
	{
		if (tmp->next && ft_strcmp(((t_varenv *)(tmp->next->content))->name, name) == 0)
		{
				prev = tmp->next;
				tmp->next = tmp->next->next;
				ft_lstdelone(&prev, del_env_var);
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
	//t_list	*tmplst;
	struct stat st;
	struct stat stg;
	int		i;
	int		y;
	int z;
	int		status;
	int		ret;
//	int 	y;
//	char 	str[PATH_MAX + 1];

	// t_varenv	*hash_tab[HASH_TAB_MAX];
	//
	// init_hash_tab(&hash_tab);


	(void)ac;
	(void)av;
	g_env_lst = NULL;
	g_env_tab = NULL;
	g_my_errno = 0;
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
		if (!strrr)
		{
			exit(0);
		}
		if (!(minishell_parser(strrr, &command)))
		{
			ft_printf("%s\n", "Le parsing a fail");
			ft_strdel(&strrr);
			continue;
		}
		ft_strdel(&strrr);
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
			**	FIN ERREURS
			*/
			/*
			**	GESTION DES BULTINS
			*/
			if (ft_strcmp(command[y][0], "exit") == 0)
			{
				exit_builtin(command[y][1]);
			}
			else if (ft_strcmp(command[y][0], "mypwd") == 0)
			{
				ft_printf("%s\n", get_env_var_by_name("PWD")->content);
				continue;
			}
			else if (ft_strcmp(command[y][0], "myoldpwd") == 0)
			{
				ft_printf("%s\n", get_env_var_by_name("OLDPWD")->content);
				continue;
			}
			else if (ft_strcmp(command[y][0], "cd") == 0)
			{
				cd_builtin(command[y]);
				ft_strtabdel(&g_env_tab);
				env_lst_to_tab(&g_env_lst, &g_env_tab);
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
					change_env_var(&g_env_lst, command[y][1], command[y][2]);
					ft_strtabdel(&g_env_tab);
					env_lst_to_tab(&g_env_lst, &g_env_tab);
					env_paths = get_env_paths(g_env_lst);
				}
				continue;
			}
			else if (ft_strcmp(command[y][0], "unsetenv") == 0)
			{
				remove_one(&g_env_lst, command[y][1]);
				ft_strtabdel(&g_env_tab);
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
			// stat du nom
			lstat(get_complete_path(NULL, command[y][0]), &stg);
			while (env_paths[++i])
			{
				ret = lstat(get_complete_path(env_paths[i], command[y][0]), &st);
				// Si le fichier existe pas dans ce path, continue a boucler
				if (ret < 0)
				{
					// Si c'etait le dernier -> pas trouve
					if (!env_paths[i + 1] && !S_ISDIR(stg.st_mode))
					{
						ft_printf("minishell: command not found: %s\n", command[y][0]);
						break;
					}
					continue;
				}
				// Si le fichier est trouvé on l'execute
				else if (ret == 0 && !S_ISDIR(st.st_mode))
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
			// ERREURS
			if (S_ISDIR(stg.st_mode) && ret < 0)
				ft_printf("minishell: %s is a directory\n", command[y][0]);
		}
		// FREE command
		z = -1;
		while (command[++z])
			ft_strtabdel(&(command[z]));
	}
	ft_strtabdel(&g_env_tab);
	ft_lstdel(&g_env_lst, del_env_var);
	return (0);
}
