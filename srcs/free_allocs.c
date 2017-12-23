/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_allocs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 16:12:44 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/23 02:20:39 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_dir_files(char *filename, char **dir_files, char *path)
{
	size_t	i;

	i = 0;
	while (dir_files[i])
	{
		ft_strdel(&(dir_files[i]));
		i += 1;
	}
	ft_strdel(&filename);
	if (path != NULL)
		ft_strdel(&path);
	free(dir_files);
}

