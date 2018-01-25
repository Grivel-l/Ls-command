/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 23:19:10 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/25 01:04:44 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int		add_option(t_opts *options, char c)
{
	if (c == 'l')
		options->l = 1;
	else if (c == 'R')
		options->R = 1;
	else if (c == 'a')
		options->a = 1;
	else if (c == 'r')
		options->r = 1;
	else if (c == 't')
		options->t = 1;
	else
	{
		invalid_option(c);
		options->error = 1;
		return (-1);
	}
	return (0);
}

static size_t	get_args_nbr(size_t argc, char **argv)
{
	size_t	i;
	size_t	args_nbr;

	i = 0;
	args_nbr = 0;
	while (i < argc - 1)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && argv[i][1] == '\0') || args_nbr > 0)
			args_nbr += 1;
		i += 1;
	}
	return (args_nbr);
}

static t_opts	set_default_options(void)
{
	t_opts	options;

	options.R = 0;
	options.a = 0;
	options.l = 0;
	options.r = 0;
	options.t = 0;
	options.error = 0;
	return (options);
}

t_opts			get_options(size_t argc, char **argv)
{
	size_t	i;
	char	*pointer;
	t_opts	options;

	options = set_default_options();
	if (argc-- <= 1)
		return (options);
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (options);
		pointer = argv[i];
		argv[i] += 1;
		if (*(argv[i]) != '-')
		{
			while (*(argv[i]))
			{
				add_option(&options, *(argv[i]));
				if (options.error)
					return (options);
				argv[i] += 1;
			}
 		}
		argv[i] = pointer;
		i += 1;
	}
	return (options);
}

static int		set_arg(t_flist **list, char *arg, size_t args_nbr, t_flist **pointer, t_opts options)
{
	t_flist	*link;
	t_list	*arg_list;

	if (*pointer == NULL)
	{
		if ((*list = new_flist(new_file(arg, "", args_nbr > 1, 1))) == NULL)
			return (-1);
		*pointer = *list;
		if (fill_infos((*list)->file, (*list)->file->filename, options) == -1)
			return (-1);
		if (!(*list)->file->exist)
			enoent_error((*list)->file->filename);
	}
	else
	{
		if ((arg_list = ft_lstnew(arg, ft_strlen(arg))) == NULL)
			return (-1);
		if ((link = set_flist_link(list, arg_list, "", options)) == NULL)
		{
			free_files(arg_list);
			return (-1);
		}
		free_files(arg_list);
		link->file->is_arg = 1;
		link->file->print_arg = args_nbr > 1;
		if (fill_infos(link->file, link->file->filename, options) == -1)
			return (-1);
		if (!link->file->exist)
			enoent_error(link->file->filename);
	}
	return (0);
}
t_flist			*get_args_list(size_t argc, char **argv, t_opts options)
{
	size_t	i;
	t_flist	*list;
	t_flist	*pointer;
	size_t	args_nbr;
	char	options_readed;

	i = 0;
	pointer = NULL;
	options_readed = 0;
	args_nbr = get_args_nbr(argc, argv);
	while (i < argc - 1)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && argv[i][1] == '\0') || options_readed)
		{
			options_readed = 1;
			if (set_arg(&list, argv[i], args_nbr, &pointer, options) == -1)
				return (NULL);
		}
		i += 1;
	}
	return (pointer == NULL ? new_flist(new_file(".", "", 0, 1)) : pointer);
}
