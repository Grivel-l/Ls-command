/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:18:53 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 02:31:28 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	enoent_error(void)
{
	ft_putstr_fd("The file doesn't exist\n", 2);
}

void		print_result(t_flist *list)
{
	while (list != NULL)
	{
		if (list->file->is_arg && !list->file->exist)
			enoent_error();
		else
		{
			ft_putstr(list->file->filename);
			print_result(list->file->file_list);
			ft_putchar('\n');
		}
		list = list->next;
	}
}
