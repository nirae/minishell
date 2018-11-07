/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/11/07 18:47:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int signal)
{
	if (signal == SIGINT)
		ft_printf("\n%s", PROMPT);
}

void	catch_signal_echo(int signal)
{
	if (signal == SIGINT)
	{
		
	}
}

void	error()
{
	ft_printf("minishell failed\n");
	exit(EXIT_FAILURE);
}

/////////////////////////////////////////////////////////////////////////////
///////////////////////// ECHO ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////

static int		echo(char *str)
{
	int i = -1;
	int y = 0;
	char *tmp;
	char final_str[4096];
	int nb_quotes = 0;
	char *line;

	signal(SIGINT, catch_signal);
	final_str[0] = 0;
	while (str[++i])
	{
		if (str[i] == ' ' && (nb_quotes % 2) == 0)
			continue;
		else if (str[i] == '\"')
		{
			nb_quotes++;
			continue;
		}
		else
		{
			final_str[y] = str[i];
			y++;
			if (str[i + 1] == ' ')
			{
				final_str[y] = ' ';
				y++;
			}
		}
		if (str[i + 1] == 0 && (nb_quotes % 2) != 0)
		{
			ft_printf("termine ta quote putain>");
			line = NULL;
			if (get_next_line(0, &line) < 0)
				error();
			if (!line[0])
				line[0] = '\n';
			tmp = str;
			str = ft_strjoin(tmp, line);
			ft_strdel(&line);
		}
	}
	final_str[y] = '\0';
	if (final_str[0])
		ft_printf("%s", final_str);
	return (TRUE);
}

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

int		minishell_parser(char *input, char ***command)
{
	if (input[0] == 0)
		return (0);
	if (!(*command = ft_strsplit(input, ' ')))
		return (0);
	return (1);
}

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
		exit(0);
	if (!(varenv->name = ft_strdup(name)))
		exit(0);
	if (!(varenv->content = ft_strdup(content)))
		exit(0);
	return (varenv);
}

void		create_my_env(t_list **lst, char **environ)
{
	int		i;
	t_list	*tmplst;
	char	**env;

	i = 0;
	while (environ[i])
	{
		// a proteger
		if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
			ft_printf("lstnew a foire\n");
		if (!(env = ft_strsplit(environ[i], '=')))
			ft_printf("strsplit a foire\n");
		tmplst->content = create_varenv(env[0], env[1]);
		if (!(*lst))
			*lst = tmplst;
		else
			ft_lstadd(lst, tmplst);
		ft_memdel((void **)&env);
		i++;
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
//	t_list	*next;
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
//		prev = tmp->next;
//		next = tmp->next;
		tmp = tmp->next;
	}
	return (0);
}

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
	pid_t	father;
	char	*line;
	char	**command;
	char	**env_paths;
	t_list	*env;
	t_list	*tmplst;
	struct stat st;
	int		i;
//	int 	y;
	char 	str[PATH_MAX + 1];

	// t_varenv	*hash_tab[HASH_TAB_MAX];
	//
	// init_hash_tab(&hash_tab);


	(void)ac;
	(void)av;
	env = NULL;
	// copie de environ
	create_my_env(&env, environ);
	//ft_lstiter(env, print_lstenv);
	env_paths = get_env_paths(env);
	/*
	** Boucle infinie du programme
	*/
	while (666)
	{
		/*// Affiche le prompt
		ft_printf("%s", PROMPT);*/
		// Surveille le signal de CTRL C
		signal(SIGINT, catch_signal);
		// Affiche le prompt
		ft_printf("\n%s", PROMPT);
		// Lis l'entree standard
		line = NULL;
		if (get_next_line(0, &line) < 0)
			error();
		/*
		**	PARSING
		*/
		if (!(minishell_parser(line, &command)))
			continue;
		/*
		**	GESTION DES BULTINS
		*/
		if (ft_strcmp(command[0], "exit") == 0)
		{
			ft_printf("c'est ca degage\n");
			if (command[1])
				exit(ft_atoi(command[1]));
			else
				exit(EXIT_SUCCESS);
		}
		else if (ft_strcmp(command[0], "mypwd") == 0)
		{
			getcwd(str, PATH_MAX + 1);
			ft_printf("pwd : %s\n", str);
			continue;
		}
		else if (ft_strcmp(command[0], "cd") == 0)
		{
			char 	oldpwd[PATH_MAX + 1];
			// recupere le pwd
			getcwd(oldpwd, PATH_MAX + 1);
			if ((chdir(command[1])) < 0)
				ft_printf("chdir failed\n");
			else
			{
				if (!(change_env_var(&env, "OLDPWD", oldpwd)))
					ft_printf("OLDPWD not found\n");
				// PWD
				char 	pwd[PATH_MAX + 1];
				// recupere le pwd
				getcwd(pwd, PATH_MAX + 1);
				if (!(change_env_var(&env, "PWD", pwd)))
					ft_printf("PWD not found\n");
				ft_printf("... moving to %s ....\n", command[1]);
			}
			continue;
		}
		else if (ft_strcmp(command[0], "env") == 0)
		{
			ft_lstiter(env, print_lstenv);
			continue;
		}
		else if (ft_strcmp(command[0], "setenv") == 0)
		{
			tmplst = ft_lstnew(NULL, sizeof(t_varenv *));
			tmplst->content = create_varenv(command[1], command[2]);
			ft_lstaddend(&env, tmplst);
			continue;
		}
		else if (ft_strcmp(command[0], "unsetenv") == 0)
		{
			remove_one(&env, command[1]);
			continue;
		}
		else if (ft_strcmp(command[0], "echo") == 0)
		{
			// y = 0;
			// while (command[1 + y])
			// {
			// 	ft_printf("%s", command[1 + y]);
			// 	y++;
			// 	if (command[1 + y])
			// 		ft_printf(" ");
			// }
			if (command[1])
				echo(&line[4]);
			ft_printf("\n");
			continue;
		}
		/*
		**	FIN DES BUILTINS
		*/
		// Recherche du fichier dans les repos du path
		i = -1;
		while (env_paths[++i])
		{
			// Si le fichier existe pas dans ce path, continue a boucler
			if ((lstat(get_complete_path(env_paths[i], command[0]), &st)) < 0)
			{
				// Si c'etait le dernier -> pas trouve
				if (!env_paths[i + 1])
				{
					ft_printf("minishell: command not found: %s\n", command[0]);
					break;
				}
				continue;
			}
			// Si le fichier est trouvé on l'execute
			else
			{
				ft_printf("tiens ton resultat de merde :\n");
				father = fork();
				if (father == 0)
					execve(get_complete_path(env_paths[i], command[0]), command, environ);
				else if (father < 0)
					ft_printf("fail\n");
				else if (father > 0)
					wait(&father);
				break;
			}
		}
		//ft_printf("tiens ton resultat de merde : %s\n", line);
		ft_strdel(&line);
	}
	return (0);
}
