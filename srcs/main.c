/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 23:34:58 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/14 20:10:50 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	exit_error(t_flist *list, char *options)
{
	if (options != NULL)
		ft_strdel(&options);
	if (list != NULL)
	{
		browse_flist_suffix(&list, free_flist);
		free(list);
	}
	return (-1);
}

int			main(int argc, char **argv)
{
	t_flist	*list;
	char	*options;

	list = NULL;
	options = NULL;
	argc = (size_t)argc;
	if ((options = get_options(argc, &(argv[1]))) == NULL)
		return (exit_error(list, options));
	if ((list = get_args_list(argc, &(argv[1]))) == NULL)
		return (exit_error(list, options));
	if (browse_flist_path(&list, options, "", read_dir) == -1)
		return (exit_error(list, options));
	if (ft_strchr(options, 'l') == NULL)
		ft_putchar('\n');
	free_args(&list);
	free(options);
	return (0);
}
