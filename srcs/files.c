/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:32:52 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/11 23:22:23 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static size_t	get_args_nbr(size_t argc, char ***argv)
{
	size_t	i;
	size_t	nbr;

	i = 1;
	nbr = 0;
	while (i < argc)
	{
		if ((*argv)[i++][0] != '-')
			nbr += 1;
	}
	return (nbr);
}

int				get_all_files(int argc, char **argv, char *options, t_arg **files)
{
	(void)options;
	size_t	valid_args_nbr;

	valid_args_nbr = get_args_nbr((size_t)argc, &argv);
	if ((*files = malloc(sizeof(t_arg) * (valid_args_nbr + 1))) == NULL)
		return (-1);
	return (0);
}
