/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 16:12:35 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/19 21:10:20 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void	swap_args(t_arg **args, size_t j)
{
	t_arg	tmp;

	tmp = (*args)[j];
	(*args)[j] = (*args)[j + 1];
	(*args)[j + 1] = tmp;
}

static void	sortby_lex(t_arg **args, size_t j)
{
	if (ft_strcmp((*args)[j].arg_name, (*args)[j + 1].arg_name) > 0)
		swap_args(args, j);
}

static void	sortby_time(t_arg **args, size_t j)
{
	if ((*args)[j].file_info.st_mtimespec.tv_sec <
			(*args)[j + 1].file_info.st_mtimespec.tv_sec)
		swap_args(args, j);
	else
	{
		if ((*args)[j].file_info.st_mtimespec.tv_sec ==
				(*args)[j + 1].file_info.st_mtimespec.tv_sec)
			sortby_lex(args, j);
	}
}

static void	sort_args(t_arg **args, char *options, size_t valid_args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*args)[i].arg_name != NULL && (*args)[i + 1].arg_name != NULL)
	{
		j = 0;
		while ((*args)[j].arg_name != NULL && (*args)[j + 1].arg_name != NULL)
		{
			if (j > 0 || (j == 0 && valid_args <= 1))
			{
				if (ft_strchr(options, 't') != NULL)
					sortby_time(args, j);
				else
					sortby_lex(args, j);
			}
			j += 1;
		}
		i += 1;
	}
}

void		sort_all(t_arg **args, char *options, size_t valid_args)
{
	sort_args(args, options, valid_args);
}
