/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dirs.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:26:37 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 02:26:09 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*get_file_path(char *path)
{
	char	*file_path;

	if (path[0] == '/' && path[1] == '\0')
	{
		if ((file_path = ft_strjoin(path, "")) == NULL)
			return (NULL);
	}
	else
	{
		if ((file_path = ft_strjoin(path, "/")) == NULL)
			return (NULL);
	}
	return (file_path);
}

static int	fill_file_infos(t_file *file, char **file_path,
	char *content, t_opts options)
{
	if ((*file_path = ft_strrealloc(*file_path, content)) == NULL)
	{
		ft_strdel(file_path);
		return (-1);
	}
	if (fill_infos(file, *file_path, options) == -1)
	{
		ft_strdel(file_path);
		return (-1);
	}
	ft_strdel(file_path);
	return (0);
}

int			fill_file(t_list *files, t_flist **list, t_arg path, t_opts options)
{
	t_flist	*link;
	char	*file_path;

	if ((file_path = get_file_path(path.content)) == NULL)
		return (-1);
	link = NULL;
	if (*list == NULL)
	{
		if ((*list = new_flist(new_file(files->content,
				file_path, path.nbr, 0))) == NULL)
		{
			ft_strdel(&file_path);
			return (-1);
		}
	}
	else
	{
		if ((link = set_flist_link(list, files, file_path, options)) == NULL)
		{
			ft_strdel(&file_path);
			return (-1);
		}
	}
	return (fill_file_infos(link == NULL ? (*list)->file : link->file,
			&file_path, files->content, options));
}

int			read_dir(t_flist **list, char *path, t_opts options)
{
	t_arg	path_arg;
	char	*file_path;

	if ((file_path = ft_strjoin((*list)->file->filename, path)) == NULL)
		return (-1);
	if (fill_infos((*list)->file, file_path, options) == -1)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	if ((*list)->file->exist &&
(*list)->file->print_arg && S_ISDIR((*list)->file->file_info.st_mode))
		print_arg((*list)->file);
	path_arg.content = file_path;
	path_arg.nbr = (*list)->file->print_arg;
	if (S_ISDIR((*list)->file->file_info.st_mode) && (*list)->file->exist &&
			get_files(&((*list)->file->file_list), path_arg, options) == -1)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	ft_strdel(&file_path);
	return (0);
}
