/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:26:03 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/16 00:57:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
**							OPTIONS
*******************************************************************************/

/*
**	Check if the option is valid, return TRUE or FALSE
*/

static int		is_valid_option(char c)
{
	if (!ft_isprint(c) || (!ft_strchr(OPTIONS_CD, c) && c != ' ') || !c)
		return (FALSE);
	return (TRUE);
}

/*
**	Set the good option in the env struct. Check the options recursively
**	- If an option is not valid (check with is_valid_option()), print the error
**	and exit the program with EXIT_FAILURE;
*/

static int		set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos]))
	{
		if (ops[pos] == 'L')
			*options |= OPT_L;
		else if (ops[pos] == 'P')
			*options |= OPT_P;
	}
	else
	{
		ft_printf("minishell: cd: illegal option -- %c\nusage: cd [-%s] [file ...]\n"
			, ops[pos], OPTIONS_CD);
		return (FALSE);
	}
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

/*
**	The parser
**
**	params: av -> arguments
**			env -> "environment" struct
**			args -> A pointer to the tree of the arguments in the main()
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- For each argument in av
**		- If the argument is a potential option
**			- Call set_options for catch it and set in env
**		- Or else, the argument is probably a file/dir
**			- Get the informations about the file with lstat and manage the
**			error if it happens. If its the last argument, return FALSE, else
**			continue
**			- Create the node for the file in the tree args
**	- Return TRUE
*/

static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (name[0] == '/')
		return (name);
	if (name[0] == '.' && name[1] == '/')
	{
		tmp = ft_strdup(&name[2]);
		ft_strdel(&name);
		name = tmp;
	}
	if (parent == NULL)
	{
		if (!(result = ft_strjoin("./", name)))
			return (NULL);
		return (result);
	}
	if (parent[ft_strlen(parent) - 1] == '/')
	{
		if (!(tmp = ft_strdup(parent)))
			return (NULL);
	}
	else
	{
		if (!(tmp = ft_strjoin(parent, "/")))
			return (NULL);
	}
	if (!(result = ft_strjoin(tmp, name)))
		return (NULL);
	ft_strdel(&tmp);
	return (result);
}

int				options_parser(char **args, int *options, int *pos_args)
{
	int				i;
	int				takeoptions;

	takeoptions = TRUE;
	i = 0;
	while (args[++i])
	{
		if (((args[i][0] == '-') && (args[i][1] != '\0')) && takeoptions)
		{
			if (args[i][1] == '-')
				takeoptions = FALSE;
			else
				set_options(args[i], options, 1);
		}
		else
		{
			*pos_args = i;
			break;
		}
	}
	return (TRUE);
}

/*******************************************************************************
**							FIN OPTIONS
*******************************************************************************/

char	*ft_strjointab(char **tab, char sep)
{
	int		i;
	int		len;
	char 	*result;
	char 	sepp[2];

	i = -1;
	len = 0;
	sepp[0] = sep;
	sepp[1] = '\0';
	if (tab == NULL)
		return (ft_strdup(sepp));
	if (!tab[0])
		return (ft_strdup(sepp));
	while (tab[++i])
		len += ft_strlen(tab[i]);
	len += i;
	// ft_printf("len = %d\n", len);
	if (!(result = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		ft_strcat(result, sepp);
		ft_strcat(result, tab[i]);
	}
	return (result);
}

void	ft_realloc_addend_tab(char ***tab, char *elem)
{
	int		i;
	char 	**tmp;

	if (*tab == NULL || !elem)
		return;
	i = -1;
	while ((*tab)[++i]);
	tmp = ft_memalloc((i + 2) * sizeof(char *));
	i = -1;
	while ((*tab)[++i])
		tmp[i] = ft_strdup((*tab)[i]);
	tmp[i] = ft_strdup(elem);
	tmp[i + 1] = NULL;
	i = -1;
	while ((*tab)[++i])
		ft_strdel(&(*tab)[i]);
	ft_strdel(&(*tab)[i]);
	ft_memdel((void **)*tab);
	*tab = tmp;
}

int		check_path_errors(char *path)
{
	struct stat st;

	// Test avec stat si le dossier existe -> sinon erreur
	if ((stat(path, &st)) < 0)
	{
		// EXISTE PAS ERREUR
		ft_printf("minishell: cd: no such file or directory: %s\n", path);
		return (FALSE);
	}
	// Si il existe
	else
	{
		// Si c'est pas un dossier -> erreur
		if (!S_ISDIR(st.st_mode))
		{
			// PAS UN DOSSIER
			ft_printf("minishell: cd: not a directory: %s\n", path);
			return (FALSE);
		}
	}
	return (TRUE);
}

int		ft_stringtab_len(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i]);
	return (i);
}

static int	build_pwd_tab(char ***arg_tab, char ***pwd_tab, int pwd_tab_len)
{
	int		i;
	char 	*tmp;

	i = -1;
	// Boucle sur chaque dossier du path donne
	while ((*arg_tab)[++i])
	{
		// Si c'est egal a '..'
		if (ft_strcmp((*arg_tab)[i], "..") == 0)
		{
			if (pwd_tab_len <= 0)
				pwd_tab_len = 1;
			ft_strdel(&(*pwd_tab)[pwd_tab_len]);
			ft_strdel(&(*pwd_tab)[pwd_tab_len - 1]);
			(*pwd_tab)[pwd_tab_len - 1] = NULL;
			if (!(*pwd_tab)[0])
				ft_realloc_addend_tab(pwd_tab, "");
			else
				pwd_tab_len--;
		}
		// Si c'est egal a '.'
		else if (ft_strcmp((*arg_tab)[i], ".") == 0)
			continue;
		// Sinon
		else
		{
			ft_realloc_addend_tab(pwd_tab, (*arg_tab)[i]);
			pwd_tab_len++;
		}
		// Reconstruction de la string du path ou on en est pour verifier
		tmp = ft_strjointab(*pwd_tab, '/');
		if (!check_path_errors(tmp))
		{
			ft_strdel(&tmp);
			return (FALSE);
		}
		ft_strdel(&tmp);
	}
	return (TRUE);
}

char	*get_final_path(char *path)
{
	char **arg_tab;
	char **pwd_tab;
	int pwd_tab_len;
	t_varenv *tmp;
	char *str;

	arg_tab = NULL;
	pwd_tab = NULL;
	// Si le path envoye commence par '.'
	if (path[0] == '/')
		return (ft_strdup(get_complete_path(get_env_var_by_name("PWD")->content, path)));
	// Creation d'un tableau de char ARG_TAB en splitant sur le path envoye
	arg_tab = ft_strsplit(path, '/');
	// Creation d'un tableau de char PWD_TAB en splitant sur la variable d'env PWD
	tmp = get_env_var_by_name("PWD");
	pwd_tab = ft_strsplit(tmp->content, '/');
	// compte le nombre d'elements de pwd_tab
	pwd_tab_len = ft_stringtab_len(pwd_tab);
	// Reconstruction du pwd avec le path envoyé
	if (!build_pwd_tab(&arg_tab, &pwd_tab, pwd_tab_len))
	{
		ft_strtabdel(&arg_tab);
		ft_strtabdel(&pwd_tab);
		return (FALSE);
	}
	str = ft_strjointab(pwd_tab, '/');
	ft_strtabdel(&arg_tab);
	ft_strtabdel(&pwd_tab);
	return (str);
}

int		change_directory(char *pwd, char *oldpwd, int options)
{
	char cwd[PATH_MAX + 1];

	if (!check_path_errors(pwd))
		return (FALSE);
	if ((chdir(pwd)) < 0)
		// Mieux gerer l'erreur
		ft_printf("chdir failed, errno = %d\n", errno);
	// Si c'est bon
	else
	{
		// Change la variable d'env OLDPWD
		if (!(change_env_var(&g_env_lst, "OLDPWD", oldpwd)))
			ft_printf("OLDPWD not found\n");
		// Change la variable d'env PWD
		if (options & OPT_P)
		{
			getcwd(cwd, PATH_MAX + 1);
			if (!(change_env_var(&g_env_lst, "PWD", cwd)))
				ft_printf("PWD not found\n");
		}
		else
		{
			if (!(change_env_var(&g_env_lst, "PWD", pwd)))
				ft_printf("PWD not found\n");
		}
	}
	return (TRUE);
}

int		cd_builtin(char **args)
{
	char 	*oldpwd = NULL;
	char 	*pwd = NULL;
	int		pos_args;
	int		options;

	options = 0;
	pos_args = 0;
	// Recupere les options
	options_parser(args, &options, &pos_args);
	// 			Debug des options
	//			ft_printf("options = %d, pos_args = %d, argument courant = %s\n", options, pos_args, args[pos_args]);
	// Recupere le oldpwd depuis l'environement
	// a proteger
	oldpwd = get_env_var_by_name("PWD")->content;
	// SI cd
	if (pos_args == 0 || !args[pos_args] || !args[pos_args][0])
		pwd = get_final_path(get_env_var_by_name("HOME")->content);
	// SI cd -
	else if (ft_strcmp(args[pos_args], "-") == 0)
		pwd = get_final_path(get_env_var_by_name("OLDPWD")->content);
	else
		pwd = get_final_path(args[pos_args]);
	if (!pwd || !change_directory(pwd, oldpwd, options))
	{
		ft_strdel(&pwd);
		return (FALSE);
	}
	ft_strdel(&pwd);
	return (TRUE);
}
