/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 23:34:58 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/25 02:39:58 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	exit_error(t_flist *list)
{
	if (list != NULL)
	{
		browse_flist_suffix(&list, free_flist);
		free(list);
	}
	return (1);
}

static int	check_existing_file(t_flist **list_start, t_opts options)
{
	options.error = 0;
	if ((*list_start)->file->exist)
		return (-1);
	return (0);
}

int			main(int argc, char **argv)
{
	t_flist	*list;
	t_opts	options;

	list = NULL;
	argc = (size_t)argc;
	options = get_options(argc, &(argv[1]));
	if (options.error)
		return (exit_error(list));
	if ((list = get_args_list(argc, &(argv[1]), options)) == NULL)
		return (exit_error(list));
	if (options.r)
	{
		if (browse_reverse_flist(&list, options, print_flist) == -1)
			return (exit_error(list));
		if (browse_reverse_flist_path(&list, options, "", read_dir) == -1)
			return (exit_error(list));
	}
	else
	{
		if (browse_flist(&list, options, print_flist) == -1)
			return (exit_error(list));
		if (browse_flist_path(&list, options, "", read_dir) == -1)
			return (exit_error(list));
	}
	if (!options.l && browse_flist(&list, options, check_existing_file) == -1)
		ft_putchar('\n');
	free_args(&list);
	return (0);
}
