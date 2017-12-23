/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   files2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/23 00:01:05 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/23 02:54:39 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		fill_infos(char **files, t_info **files_info, char *filename)
{
	char 	*path;
	char	*files_pointer;
	t_info	*info_pointer;

	if ((*files_info = malloc(sizeof(t_info) * (ft_tablen(files) + 1))) == NULL)
		return (-1);
	files_pointer = *files;
	info_pointer = *files_info;
	while (*files != NULL)
	{
		if ((path = ft_strjoin(filename, (const char *)*files)) == NULL)
			return (-1);
		if ((stat(path, &((*files_info)->stats)) == -1) ||
				(((*files_info)->name = ft_strdup(*files)) == NULL))
			return (-1);
		free(path);
		*files_info += 1;
		files += 1;
	}
	(*files_info)->name = NULL;
	*files_info = info_pointer;
	return (0);
}

size_t	count_dirs(t_info *files_info)
{
	size_t	i;

	i = 0;
	while ((*files_info).name != NULL)
	{
		if (S_ISDIR((*files_info).stats.st_mode))
			i += 1;
		files_info += 1;
	}
	return (i);
}
