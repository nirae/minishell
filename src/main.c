/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/10/09 18:37:06 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int signal)
{
	if (signal == SIGINT)
		ft_printf("\n%s", PROMPT);
	//printf("coucou\n");
}

void	error()
{
	ft_printf("minishell failed\n");
	exit(EXIT_FAILURE);
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

char		**get_my_env(char **environ)
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
}

int		main(int ac, char **av, char **environ)
{
	pid_t	father;
	char	*line;
	char	**command;
	char	**env_path;
	char	**env;
	char	**tmp;
	struct stat st;
	int		i;
	int 	y;
	char 	str[PATH_MAX + 1];

	(void)ac;
	(void)av;
	// copie de environ
	env = get_my_env(environ);
	/*
	**	Recupere tous les repos de PATH
	*/
	i = -1;
	while (env[++i])
	{
		tmp = ft_strsplit(env[i], '=');
		if (ft_strcmp(tmp[0], "PATH") == 0)
			env_path = ft_strsplit(tmp[1], ':');
		ft_memdel((void **)&tmp);
	}
	/*
	**
	*/
	while (666)
	{
		// Affiche le prompt
		ft_printf("%s", PROMPT);
		// Surveille le signal de CTRL C
		signal(SIGINT, catch_signal);
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

				// Mettre a jour PWD et OLDPWD dans l'env
				// OLDPWD
				i = -1;
				while (env[++i])
				{
					tmp = ft_strsplit(env[i], '=');
					if (ft_strcmp(tmp[0], "OLDPWD") == 0)
					{
						ft_memdel((void **)&env[i]);
						if (!(env[i] = ft_strjoin("OLDPWD=", oldpwd)))
							ft_printf("strjoin failed\n");
					}
				}
				// PWD
				char 	pwd[PATH_MAX + 1];
				// recupere le pwd
				getcwd(pwd, PATH_MAX + 1);
				i = -1;
				while (env[++i])
				{
					tmp = ft_strsplit(env[i], '=');
					if (ft_strcmp(tmp[0], "PWD") == 0)
					{
						ft_memdel((void **)&env[i]);
						if (!(env[i] = ft_strjoin("PWD=", pwd)))
							ft_printf("strjoin failed\n");
					}
				}
				//
				ft_printf("moving to %s\n", command[1]);
			}
			continue;
		}
		else if (ft_strcmp(command[0], "env") == 0)
		{
			int y = -1;
			if (env)
			{
				while (env[++y])
					ft_printf("%s\n", env[y]);
			}
			continue;
		}
		else if (ft_strcmp(command[0], "echo") == 0)
		{
			y = 0;
			while (command[1 + y])
			{
				ft_printf("%s", command[1 + y]);
				y++;
				if (command[1 + y])
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
		while (env_path[++i])
		{
			// Si le fichier existe pas dans ce path, continue a boucler
			if ((lstat(get_complete_path(env_path[i], command[0]), &st)) < 0)
			{
				// Si c'etait le dernier -> pas trouve
				if (!env_path[i + 1])
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
					execve(get_complete_path(env_path[i], command[0]), command, env);
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
