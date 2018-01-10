/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dirs.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:26:37 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/27 00:41:44 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_file(t_list *files, t_flist **list, char *path, char *options)
{
	t_flist	*link;
	char	*file_path;

	if ((file_path = ft_strjoin(path, "/")) == NULL)
		return (-1);
	link = NULL;
	if (*list == NULL)
	{
		if ((*list = new_flist(new_file(files->content, file_path, 0))) == NULL)
			return (-1);
	}
	else
	{
		if ((link = set_flist_link(list, files, file_path, options)) == NULL)
			return (-1);
	}
	if ((file_path = ft_strrealloc(file_path, files->content)) == NULL)
		return (-1);
	if (fill_infos(link == NULL ? (*list)->file : link->file, file_path, options) == -1)
		return (-1);
	ft_strdel(&file_path);
	return (0);
}

static int	recursive(t_flist **list, char *options)
{
	char	*file_path;

	if ((file_path = ft_strjoin((*list)->file->path, (*list)->file->filename)) == NULL)
		return (-1);
	if (S_ISDIR((*list)->file->file_info.st_mode) &&
		ft_strcmp((*list)->file->filename, ".") != 0 &&
		ft_strcmp((*list)->file->filename, "..") != 0)
	{
		if (get_files(&((*list)->file->file_list), file_path, options) == -1)
			return (-1);
	}
	ft_strdel(&file_path);
	return (0);
}

int			get_files(t_flist **list, char *path, char *options)
{
	t_list	*files;
	t_flist	**list_start;
	t_list	*previous_file;

	if ((files = ft_readdir(path, ft_strchr(options, 'a') != NULL)) == NULL)
	{
		check_errno(path);
		return (errno == EACCES ? -2 : -1);
	}
	list_start = list;
	if (files->content_size == 0)
	{
		free(files->content);
		free(files);
		files = NULL;
	}
	while (files != NULL)
	{
		if (fill_file(files, list_start, path, options) == -1)
			return (-1);
		previous_file = files;
		files = files->next;
		free(previous_file->content);
		free(previous_file);
	}
	print_flist(list_start, options);
	if (ft_strchr(options, 'R') != NULL)
		browse_flist(list_start, options, recursive);
	browse_flist_suffix(list_start, free_flist);
	if ((*list_start) == NULL)
		print_void_arg(path);
	free(*list_start);
	*list_start = NULL;
	return (0);
}

int			read_dir(t_flist **list, char *path, char *options)
{
	char	*file_path;

	if ((file_path = ft_strjoin((*list)->file->filename, path)) == NULL)
		return (-1);
	if ((*list)->file->print_arg)
		print_arg(file_path);
	if (fill_infos((*list)->file, file_path, options) == -1)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	if (get_files(&((*list)->file->file_list),
				file_path, options) == -1)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	ft_strdel(&file_path);
	return (0);
}
