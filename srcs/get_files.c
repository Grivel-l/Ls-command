/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_files.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 02:01:42 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 02:28:56 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	recursive(t_flist **list, t_opts options)
{
	t_arg	path;

	if ((path.content =
				ft_strjoin((*list)->file->path, (*list)->file->filename)) == NULL)
		return (-1);
	if (S_ISDIR((*list)->file->file_info.st_mode) &&
			ft_strcmp((*list)->file->filename, ".") != 0 &&
			ft_strcmp((*list)->file->filename, "..") != 0)
	{
		path.nbr = 1;
		if (get_files(&((*list)->file->file_list), path, options) == -1)
		{
			ft_strdel(&(path.content));
			return (-1);
		}
	}
	ft_strdel(&(path.content));
	return (0);
}

int			get_files(t_flist **list, t_arg path_arg, t_opts options)
{
	t_flist	*tmp;
	t_list	*files;
	char	*tmp_path;
	t_flist	**list_start;
	t_list	*previous_file;

	if ((files = ft_readdir(path_arg.content, options.a)) == NULL)
	{
		if (errno == EACCES)
		{
			if ((tmp_path = ft_strjoin(path_arg.content, "/")) == NULL)
				return (-1);
			if ((tmp = new_flist(new_file(path_arg.content, tmp_path, 1, 0))) == NULL)
				return (-1);
			tmp->file->eacces = 1;
			tmp->file->print_arg = path_arg.nbr;
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
		if (fill_file(files, list_start, path_arg, options) == -1)
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
	if (path_arg.nbr && (*list_start) == NULL)
		print_void_arg(path_arg.content, options);
	free(*list_start);
	*list_start = NULL;
	return (0);
}
