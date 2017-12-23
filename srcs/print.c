/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/13 18:59:58 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/23 03:16:49 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void	print_files(t_file *files)
{
	size_t	i;

	i = 0;
	if (files != NULL) {
		while (files[i].filename != NULL)
		{
			if (i > 0)
				ft_putstr("     ");
			ft_putstr(files[i].filename);
			i += 1;
		}
		ft_putchar('\n');
	}
}

static void	print_sub_dirs(t_arg *args, size_t valid_args)
{
	size_t	i;

	i = 0;
	while (args[i].arg_name != NULL)
	{
		ft_putstr(args[i].arg_name);
		ft_putchar('\n');
		i += 1;
		(void)valid_args;
		// dprintf(1, "Parent: %s\n", args[i].arg_name);
		// dprintf(1, "Sub dir: %p\n", args[i].sub_dir[0].arg_name);
		// print_result(args[i].sub_dir, valid_args);
	}
}

void		print_result(t_arg *args, size_t valid_args)
{
	size_t	i;

	i = 0;
	while (args[i].arg_name != NULL)
	{
		if (i == 0 && args[i + 1].arg_name == NULL)
			print_files(args[i].files);
		else
		{
			if (i != 0)
				ft_putchar('\n');
			if ((valid_args > 1) || (valid_args <= 1 && i != 0))
			{
				ft_putstr(args[i].arg_name);
				ft_putstr(":\n");
			}
			print_files(args[i].files);
		}
		print_sub_dirs(args[i].sub_dir, valid_args);
		i += 1;
	}
}
