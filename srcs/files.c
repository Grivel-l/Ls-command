/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   files.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:32:52 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/14 17:37:29 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static size_t	get_args_nbr(size_t argc, char ***argv)
{
	size_t	i;
	size_t	nbr;

	i = 1;
	nbr = 0;
	while (i < argc)
	{
		if ((*argv)[i++][0] != '-')
			nbr += 1;
	}
	return (nbr);
}

static int		manage_dir(t_arg **files, size_t *index, char *filename, char *options)
{
	size_t	i;
	char	**dir_files;

	dir_files = ft_readdir(filename, ft_strchr(options, 'a') != NULL);
	if (((*files)[*index].files = malloc(sizeof(t_file) * (ft_tablen(dir_files) + 1))) == NULL)
		return (-1);
	i = 0;
	while (dir_files[i])
	{
		(*files)[*index].files[i].path = NULL;
		if (((*files)[*index].files[i].filename = ft_strdup(dir_files[i])) == NULL)
		{
			free((*files)[*index].files);
			return (-1);
		}
		if (ft_strchr(options, 'l') != NULL)
			if (stat(ft_strjoin(filename, (const char *)dir_files[i]), &((*files)[*index].files[i].file_info)) == -1)
				return (-1);
		i += 1;
	}
	(*files)[*index].files[i].filename = NULL;
	dir_files[i] = NULL;
	free(filename);
	return (0);
}

static int		read_dir(char *filename, t_arg **files, char *options, size_t *index)
{
	if (*index > 0)
		if (realloc_files(files, *index) == -1)
			return (-1);
	if (stat((const char *)filename, &((*files)[*index].file_info)) == -1)
		return (-1);
	(*files)[*index].is_file = !S_ISDIR((*files)[*index].file_info.st_mode);
	if (((*files)[*index].arg_name = ft_strdup(filename)) == NULL)
		return (-1);
	if (!(*files)[*index].is_file)
		return (manage_dir(files, index, ft_strjoin(filename, "/"), options));
	return (0);
}

int				get_all_files(size_t argc, char **argv, char *options, t_arg **files)
{
	size_t	i;
	size_t	*index;
	size_t	valid_args_nbr;

	valid_args_nbr = get_args_nbr(argc, &argv);
	if (((index = malloc(sizeof(size_t))) == NULL) || ((*files = malloc(sizeof(t_arg) * 2)) == NULL))
		return (-1);
	*index = 0;
	if (valid_args_nbr == 0)
	{
		if (read_dir(".", files, options, index) == -1)
			return (-1);
		(*files)[1].arg_name = NULL;
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			if (argv[i][0] != '-')
			{
				if (read_dir(argv[i], files, options, index) == -1)
					return (-1);
				*index += 1;
				(*files)[*index].arg_name = NULL;
			}
			i += 1;
		}
	}
	return (0);
}
