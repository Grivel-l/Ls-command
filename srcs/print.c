/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/13 18:59:58 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 18:32:44 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_files(t_file *files)
{
	size_t	i;

	i = 0;
	while (files[i].filename)
	{
		if (i > 0)
			ft_putstr("     ");
		ft_putstr(files[i].filename);
		i += 1;
	}
	ft_putchar('\n');
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
		i += 1;
	}
}
