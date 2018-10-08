/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/10/08 21:23:47 by ndubouil         ###   ########.fr       */
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

int		main(int ac, char **av, char **env)
{
	pid_t	father;
	char	*line;
	char	**command;
	char	**env_path;
	char	**tmp;
	struct stat st;
	int		i;
	int 	y;
	char 	str[PATH_MAX + 1];

	(void)ac;
	(void)av;
	while (666)
	{
		// Affiche le prompt
		ft_printf("%s", PROMPT);
		// Surveille le signal de ctrl C
		signal(SIGINT, catch_signal);
		// Lis l'entree standard
		if (get_next_line(0, &line) < 0)
			error();
		ft_printf("%s\n", line);
		// recupere la commande et les arguments
		command = ft_strsplit(line, ' ');
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
			if ((chdir(command[1])) < 0)
				ft_printf("chdir failed\n");
			else
				ft_printf("moving to %s\n", command[1]);
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
		// recupere la commande et les arguments
		//command = ft_strsplit(line, ' ');
		// recupere la liste du path environnement
		i = -1;
		while (env[++i])
		{
			tmp = ft_strsplit(env[i], '=');
			if (ft_strcmp(tmp[0], "PATH") == 0)
				env_path = ft_strsplit(tmp[1], ':');
			ft_memdel((void **)&tmp);
		}
		// Boucle sur tous les chemins de l'env path
		i = -1;
		while (env_path[++i])
		{
			// Si le fichier existe pas dans ce path, continue a boucler
			if ((lstat(get_complete_path(env_path[i], command[0]), &st)) < 0)
				continue;
			// Si le fichier est trouvé on l'execute
			ft_printf("tiens ton resultat de merde :\n");
			father = fork();
			if (father == 0)
				execve(get_complete_path(env_path[i], command[0]), command, env);
			else if (father < 0)
				ft_printf("fail\n");
			else if (father > 0)
				wait(&father);
		}
		//ft_printf("tiens ton resultat de merde : %s\n", line);
		ft_strdel(&line);
	}
	return (0);
}
