/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/13 18:59:58 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/13 19:13:22 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	print_result(t_arg *files)
{
	size_t	i;
	size_t	j;

	i = 0;
	dprintf(1, "\n\nPrint result\n\n");
	while (files[i].arg_name != NULL)
	{
		printf("Arg name: %s\n", files[i].arg_name);
		j = 0;
		while (files[i].files[j].filename)
		{
			printf("File: %s\n", files[i].files[j].filename);
			j += 1;
		}
		printf("\n");
		i += 1;
	}
}
