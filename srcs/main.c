/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 16:32:52 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/23 00:47:52 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void	free_files(t_file *files)
{
	size_t	i;

	i = 0;
	while (files[i].filename != NULL)
	{
		if (files[i].path != NULL)
			ft_strdel(&(files[i].path));
		ft_strdel(&(files[i].filename));
		i += 1;
	}
	free(files);
}

static void	free_args(char *options, t_arg *args)
{
	size_t	i;

	if (options != NULL)
	 	ft_strdel(&options);
	i = 0;
	while (args[i].arg_name != NULL)
	{
		free_files(args[i].files);
		ft_strdel(&(args[i].arg_name));
		i += 1;
	}
	free(args);
}

int			main(int argc, char **argv)
{
	t_arg	*args;
	char	*options;
	size_t	valid_args;

	if ((options = get_options(argc, &argv[1])) == NULL)
		return (-1);
	if (get_all_files((size_t)argc, argv, options, &args) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	valid_args = get_valid_args_nbr(argc, &argv);
	// sort_all(&args, options, valid_args);
	print_result(args, valid_args);
	// ft_puttab(files);
	free_args(options, args);
	return (0);
}
