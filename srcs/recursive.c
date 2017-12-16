/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   recursive.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/16 15:48:31 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/16 21:02:54 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static size_t	argslen(t_arg **files)
{
	size_t	i;

	i = 0;
	while ((*files)[i].arg_name != NULL)
		i += 1;
	return (i);
}

static int		is_valid_dir(t_arg **args, size_t arg_i, size_t i)
{
	return ((S_ISDIR((*args)[arg_i].files[i].file_info.st_mode)) &&
				(ft_strcmp((*args)[arg_i].files[i].filename, ".") != 0) &&
				(ft_strcmp((*args)[arg_i].files[i].filename, "..") != 0));
}

static int		add_path(t_arg arg, size_t i, char **pointer, char **filename)
{
	if ((*filename = ft_strjoin(arg.arg_name,
					"/")) == NULL)
		return (-1);
	*pointer = *filename;
	if ((*filename = ft_strjoin(*filename,
					arg.files[i].filename)) == NULL)
		return (-1);
	return (0);
}

static int		read_files(size_t arg_i, t_arg **args, char *options)
{
	size_t	i;
	size_t	index;
	char	*pointer;
	char	*filename;

	i = 0;
	index = argslen(args);
	while ((*args)[arg_i].files[i].filename != NULL)
	{
		if (is_valid_dir(args, arg_i, i))
		{
			if (add_path((*args)[arg_i], i, &pointer, &filename) == -1)
				return (-1);
			if (read_dir(filename, args, options, index) == -1)
			{
				free(pointer);
				return (-1);
			}
			free(pointer);
			index += 1;
			(*args)[index].arg_name = NULL;
		}
		i += 1;
	}
	return (0);
}

int				launch_recursive(t_arg **args, char *options)
{
	size_t	i;

	i = 0;
	while ((*args)[i].arg_name != NULL)
	{
		if (read_files(i, args, options) == -1)
			return (-1);
		i += 1;
	}
	return (0);
}
