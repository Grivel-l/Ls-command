/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 23:34:58 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/26 22:40:03 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	t_flist	*list;
	char	*options;

	if ((options = get_options(argc, &(argv[1]))) == NULL)
		return (-1);
	if ((list = get_args_list(argc, &(argv[1]))) == NULL)
		return (-1);
	if (read_dir(&list, "", options) == -1)
		return (-1);
	// print_result(list);
	// free_args(list);
	free(options);
	return (0);
}
