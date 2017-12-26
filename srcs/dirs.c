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

static int	fill_infos(t_file *file, char *path)
{
	if (lstat(path, &(file->file_info)) == -1)
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

static int	fill_file(t_list *files, t_flist **list,
		char *path, t_flist **list_start)
{
	char	*file_path;

	if ((file_path = ft_strjoin(path, "/")) == NULL)
		return (-1);
	if (*list_start == NULL)
	{
		if ((*list = new_flist(new_file(files->content, file_path, 0))) == NULL)
			return (-1);
		*list_start = *list;
	}
	else
	{
		if (((*list)->next = new_flist(new_file(files->content, file_path, 0))) == NULL)
			return (-1);
		*list = (*list)->next;
	}
	if ((file_path = ft_strrealloc(file_path, files->content)) == NULL)
		return (-1);
	if (fill_infos((*list)->file, file_path) == -1)
		return (-1);
	ft_strdel(&file_path);
	return (0);
}

static int	launch_recursive(t_flist **list_start, char *options)
{
	t_flist **list;
	char	*file_path;

	list = list_start;
	while (*list != NULL)
	{
		if ((file_path = ft_strjoin((*list)->file->path, (*list)->file->filename)) == NULL)
			return (-1);
		if (S_ISDIR((*list)->file->file_info.st_mode) &&
			ft_strcmp((*list)->file->filename, ".") != 0 &&
			ft_strcmp((*list)->file->filename, "..") != 0)
			if (get_files(&((*list)->file->file_list), file_path, options) == -1)
				return (-1);
		*list = (*list)->next;
		ft_strdel(&file_path);
	}
	*list = *list_start;
	return (0);
}

int			get_files(t_flist **list, char *path, char *options)
{
	t_list	*files;
	t_flist	*list_start;
	t_list	*previous_file;

	if ((files = ft_readdir(path, ft_strchr(options, 'a') != NULL)) == NULL)
		return (-1);
	list_start = NULL;
	while (files != NULL && files->content_size > 0)
	{
		if (fill_file(files, list, path, &list_start) == -1)
			return (-1);
		previous_file = files;
		files = files->next;
		free(previous_file->content);
		free(previous_file);
	}
	*list = list_start;
	sort_print(list, options);
	if (ft_strchr(options, 'R') != NULL)
		return (launch_recursive(list, options));
	return (0);
}

int			read_dir(t_flist **list, char *path, char *options)
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
		if ((*list)->file->is_arg)
			if (get_files(&((*list)->file->file_list),
						file_path, options) == -1)
				return (-1);
		ft_strdel(&file_path);
		*list = (*list)->next;
	}
	*list = start;
	return (0);
}
