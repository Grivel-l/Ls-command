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

void	free_stuff(char *options, char **files)
{
	size_t	i;

	free(options);
	i = 0;
	while (files[i])
		ft_strdel(&files[i++]);
	free(files);
}

int		main(int argc, char **argv)
{
	char	**files;
	char	*options;

	options = get_options(argc, &argv[1]);
	ft_putstr(options);
	files = read_dir(argv[1]);
	free_stuff(options, files);
	return (0);
}
