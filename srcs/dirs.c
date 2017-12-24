/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dirs.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:26:37 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 02:00:52 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_infos(t_file *file, char *path)
{
	if (stat(path, &(file->file_info)) == -1)
	{
		if (errno == ENOENT)
			file->exist = 0;
		else
			return (-1);
	}
	else
		file->exist = 1;
	return (0);
}

int			read_dir(t_flist **list, char *path)
{
	t_flist	*start;
	char	*file_path;

	start = *list;
	while (*list != NULL)
	{
		if ((file_path = ft_strjoin((*list)->file->filename, path)) == NULL)
			return (-1);
		if (fill_infos((*list)->file, file_path) == -1)
		{
			ft_strdel(&file_path);
			return (-1);
		}
		ft_strdel(&file_path);
		*list = (*list)->next;
	}
	*list = start;
	return (0);
}
