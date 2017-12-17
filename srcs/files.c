/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   files.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:32:52 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/16 21:38:10 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

size_t			get_valid_args_nbr(size_t argc, char ***argv)
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

static int		manage_dir(t_arg **files, size_t index,
		char *filename, char *options)
{
	size_t	i;
	char	*path;
	char	**dir_files;

	if ((dir_files = ft_readdir(filename, ft_strchr(options, 'a') != NULL)) == NULL)
		return (-1);
	if (((*files)[index].files =
				malloc(sizeof(t_file) * (ft_tablen(dir_files) + 1))) == NULL)
		return (-1);
	i = 0;
	while (dir_files[i])
	{
		(*files)[index].files[i].path = NULL;
		if ((((*files)[index].files[i].filename =
					ft_strdup(dir_files[i])) == NULL) ||
			((path = ft_strjoin(filename, (const char*)dir_files[i])) == NULL) ||
			stat(path, &((*files)[index].files[i].file_info)) == -1)
			return (-1);
		i += 1;
	}
	(*files)[index].files[i].filename = NULL;
	free_dir_files(filename, dir_files, path);
	return (0);
}

static int		manage_args(size_t argc, char **argv,
		t_arg **args, char *options)
{
	size_t	i;
	size_t	index;

	i = 1;
	index = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			if (read_dir(argv[i], args, options, index) == -1)
				return (-1);
			index += 1;
			(*args)[index].arg_name = NULL;
		}
		i += 1;
	}
	return (0);
}

int				read_dir(char *filename, t_arg **files,
		char *options, size_t index)
{
	if (index > 0)
		if (realloc_files(files, index) == -1)
			return (-1);
	if (stat((const char *)filename, &((*files)[index].file_info)) == -1)
		return (-1);
	(*files)[index].is_file = !S_ISDIR((*files)[index].file_info.st_mode);
	if (((*files)[index].arg_name = ft_strdup(filename)) == NULL)
		return (-1);
	if (!(*files)[index].is_file)
		return (manage_dir(files, index, ft_strjoin(filename, "/"), options));
	return (0);
}

int				get_all_files(size_t argc, char **argv,
		char *options, t_arg **files)
{
	size_t	valid_args_nbr;

	valid_args_nbr = get_valid_args_nbr(argc, &argv);
	if (((*files = malloc(sizeof(t_arg) * 2)) == NULL))
		return (-1);
	if (valid_args_nbr == 0)
	{
		if (read_dir(".", files, options, 0) == -1)
			return (-1);
		(*files)[1].arg_name = NULL;
	}
	else
	{
		if (manage_args(argc, argv, files, options) == -1)
			return (-1);
	}
	if (ft_strchr(options, 'R') != NULL)
		return (launch_recursive(files, options));
	return (0);
}
