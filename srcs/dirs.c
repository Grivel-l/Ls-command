/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dirs.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:26:37 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 19:32:33 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_file(t_list *files, t_flist **list, char *path, t_opts options, size_t print_arg)
{
	t_flist	*link;
	char	*file_path;

	if ((file_path = ft_strjoin(path, "/")) == NULL)
		return (-1);
	link = NULL;
	if (*list == NULL)
	{
		if ((*list = new_flist(new_file(files->content, file_path, print_arg, 0))) == NULL)
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
	if ((file_path = ft_strrealloc(file_path, files->content)) == NULL)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	if (fill_infos(link == NULL ? (*list)->file : link->file, file_path, options) == -1)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	ft_strdel(&file_path);
	return (0);
}

static int	recursive(t_flist **list, t_opts options)
{
	char	*file_path;

	if ((file_path = ft_strjoin((*list)->file->path, (*list)->file->filename)) == NULL)
		return (-1);
	if (S_ISDIR((*list)->file->file_info.st_mode) &&
		ft_strcmp((*list)->file->filename, ".") != 0 &&
		ft_strcmp((*list)->file->filename, "..") != 0)
	{
		if (get_files(&((*list)->file->file_list), file_path, options, 1) == -1)
		{
			ft_strdel(&file_path);
			return (-1);
		}
	}
	ft_strdel(&file_path);
	return (0);
}

int			get_files(t_flist **list, char *path, t_opts options, size_t print_arg)
{
	t_flist	*tmp;
	t_list	*files;
	char	*tmp_path;
	t_flist	**list_start;
	t_list	*previous_file;

	if ((files = ft_readdir(path, options.a)) == NULL)
	{
		if (errno == EACCES)
		{
			if ((tmp_path = ft_strjoin(path, "/")) == NULL)
				return (-1);
			if ((tmp = new_flist(new_file(path, tmp_path, 1, 0))) == NULL)
				return (-1);
			tmp->file->eacces = 1;
			if (print_flist(&tmp, options) == -1)
			{
				ft_strdel(&tmp_path);
				free_args(&tmp);
				return (-1);
			}
			ft_strdel(&tmp_path);
			free_args(&tmp);
			return (-2);
		}
		return (-1);
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
		if (fill_file(files, list_start, path, options, print_arg) == -1)
		{
			free_files(files);
			return (-1);
		}
		previous_file = files;
		files = files->next;
		free(previous_file->content);
		free(previous_file);
	}
	if (print_flist(list_start, options) == -1)
		return (-1);
	if (options.R)
	{
		if (options.r)
		{
			if (browse_reverse_flist(list_start, options, recursive) == -1)
				return (-1);
		}
		else
		{
			if (browse_flist(list_start, options, recursive) == -1)
				return (-1);
		}
	}
	browse_flist_suffix(list_start, free_flist);
	if ((*list_start) == NULL)
		print_void_arg(path, options);
	free(*list_start);
	*list_start = NULL;
	return (0);
}

int			read_dir(t_flist **list, char *path, t_opts options)
{
	char	*file_path;

	if ((file_path = ft_strjoin((*list)->file->filename, path)) == NULL)
		return (-1);
	if (fill_infos((*list)->file, file_path, options) == -1)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	if ((*list)->file->exist && (*list)->file->print_arg && S_ISDIR((*list)->file->file_info.st_mode))
		print_arg((*list)->file);
	if (S_ISDIR((*list)->file->file_info.st_mode) && (*list)->file->exist && get_files(&((*list)->file->file_list), file_path, options, (*list)->file->print_arg) == -1)
	{
		ft_strdel(&file_path);
		return (-1);
	}
	if (!S_ISDIR((*list)->file->file_info.st_mode))
	{
		if (print_flist(list, options) == -1)
		{
			ft_strdel(&file_path);
			return (-1);
		}
	}
	ft_strdel(&file_path);
	return (0);
}
