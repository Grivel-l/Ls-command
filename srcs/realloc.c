/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 16:38:16 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/16 20:52:59 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static size_t	get_files_length(t_file *files)
{
	size_t	i;

	i = 0;
	while (files[i].filename != NULL)
		i += 1;
	return (i);
}

static t_file	*filesdup(t_file *files)
{
	t_file	*new_files;
	t_file	*new_files_pointer;

	if ((new_files = malloc(sizeof(t_file) *
					(get_files_length(files) + 1))) == NULL)
		return (NULL);
	new_files_pointer = new_files;
	while (files->filename != NULL)
	{
		if ((new_files->filename = ft_strdup(files->filename)) == NULL)
			return (NULL);
		new_files->path = NULL;
		if (files->path != NULL)
		{
			if ((new_files->path = ft_strdup(files->path)) == NULL)
				return (NULL);
			free(files->path);
		}
		new_files++->file_info = files->file_info;
		free(files++->filename);
	}
	new_files->filename = NULL;
	return (new_files_pointer);
}

static int		copy_content(t_arg *new_args, t_arg **args)
{
	if ((new_args->files = filesdup((**args).files)) == NULL)
		return (-1);
	free((**args).files);
	new_args->is_file = (**args).is_file;
	if ((new_args->arg_name = ft_strdup((**args).arg_name)) == NULL)
		return (-1);
	free((**args).arg_name);
	new_args->file_info = (**args).file_info;
	return (0);
}

int				realloc_files(t_arg **args, size_t index)
{
	t_arg	*new_args;
	t_arg	*args_pointer;
	t_arg	*new_args_pointer;

	dprintf(1, "HelloWorld index: %zu\n", index);
	if ((new_args = malloc(sizeof(t_arg) * (2 + index))) == NULL)
		return (-1);
	dprintf(1, "HelloWorld\n");
	args_pointer = *args;
	new_args_pointer = new_args;
	while ((**args).arg_name != NULL)
	{
		if (copy_content(new_args, args) == -1)
			return (-1);
		(*args) += 1;
		new_args += 1;
	}
	new_args->arg_name = NULL;
	free(args_pointer);
	*args = new_args_pointer;
	return (0);
}
