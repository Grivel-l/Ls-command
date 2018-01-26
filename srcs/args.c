/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 23:19:10 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 01:02:34 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	get_args_nbr(size_t argc, char **argv)
{
	size_t	i;
	size_t	args_nbr;

	i = 0;
	args_nbr = 0;
	while (i < argc - 1)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' &&
				argv[i][1] == '\0') || args_nbr > 0)
			args_nbr += 1;
		i += 1;
	}
	return (args_nbr);
}

static int		treate_arg(t_file *file, t_opts options)
{
	if (file == NULL)
		return (-1);
	file->is_arg = 1;
	if (fill_infos(file, file->filename, options) == -1)
		return (-1);
	if (!file->exist)
		enoent_error(file->filename);
	return (0);
}

static int		set_arg(t_flist **list, t_arg arg,
	t_flist **pointer, t_opts options)
{
	t_flist	*link;
	t_list	*arg_list;

	if (*pointer == NULL)
	{
		*list = new_flist(new_file(arg.content, "", arg.nbr > 1, 1));
		*pointer = *list;
		if (treate_arg(*list == NULL ? NULL : (*list)->file, options) == -1)
			return (-1);
	}
	else
	{
		if ((arg_list = ft_lstnew(arg.content, ft_strlen(arg.content))) == NULL)
			return (-1);
		if ((link = set_flist_link(list, arg_list, "", options)) == NULL)
		{
			free_files(arg_list);
			return (-1);
		}
		free_files(arg_list);
		link->file->print_arg = arg.nbr > 1;
		if (treate_arg(link->file, options) == -1)
			return (-1);
	}
	return (0);
}

static t_flist	*check_void_list(t_flist *list,
	t_flist *pointer, t_opts options)
{
	if (pointer == NULL)
	{
		list = new_flist(new_file(".", "", 0, 1));
		if (fill_infos(list->file, list->file->filename, options) == -1)
			return (NULL);
		return (list);
	}
	return (pointer);
}

t_flist			*get_args_list(size_t argc, char **argv, t_opts options)
{
	size_t	i;
	t_arg	arg;
	t_flist	*list;
	t_flist	*pointer;
	char	options_readed;

	i = 0;
	pointer = NULL;
	options_readed = 0;
	arg.nbr = get_args_nbr(argc, argv);
	while (i < argc - 1)
	{
		if (argv[i][0] != '-' ||
			(argv[i][0] == '-' && argv[i][1] == '\0') || options_readed)
		{
			options_readed = 1;
			arg.content = argv[i];
			if (set_arg(&list, arg, &pointer, options) == -1)
				return (NULL);
		}
		i += 1;
	}
	return (check_void_list(list, pointer, options));
}
