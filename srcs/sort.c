/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 23:54:59 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/14 22:22:24 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	sort_time(t_file *file, t_list *target)
{
	long		result;
	struct stat	target_info;
	char		*target_path;

	if ((target_path = ft_strjoin(file->path, target->content)) == NULL)
		return (-1);
	if (stat(target_path, &target_info) == -1)
		return (-1);
	ft_strdel(&target_path);
	result = file->file_info.st_mtimespec.tv_sec - target_info.st_mtimespec.tv_sec;
	if (result < 0)
		return (1);
	else if (result > 0)
		return (0);
	else
		return (2);
}

static int sort_alpha(t_file *file, t_list *target)
{
	return (ft_strcmp(file->filename, target->content) < 0 ? 0 : 1);
}

static int	sort(t_file *file, t_list *target, size_t time_sort)
{
	int		are_equal;

	if (ft_strcmp(file->filename, ".") == 0 ||
		ft_strcmp(file->filename, "..") == 0)
		return (0);
	if (ft_strcmp(target->content, ".") == 0 ||
		ft_strcmp(target->content, "..") == 0)
		return (1);
	are_equal = 2;
	if (time_sort)
		are_equal = sort_time(file, target);
	if (are_equal == -1)
		return (-1);
	if (are_equal == 2)
		return (sort_alpha(file, target));
	else
		return (are_equal);
}

t_flist	*set_flist_link(t_flist **list_start,
				t_list *files, char *path, t_opts options)
{
	t_flist	*list;
	int		sort_result;

	list = *list_start;
	while (list != NULL)
	{
		if ((sort_result = sort(list->file, files, options.t)) == -1)
			return (NULL);
		else if (sort_result == 0)
		{
			if (list->left == NULL)
			{
				if ((list->left =
			new_flist(new_file(files->content, path, 0, 0))) == NULL)
					return (NULL);
				list = list->left;
				break ;
			}
			else
				list = list->left;
		}
		else
		{
			if (list->right == NULL)
			{
				if ((list->right =
			new_flist(new_file(files->content, path, 0, 0))) == NULL)
					return (NULL);
				list = list->right;
				break ;
			}
			else
				list = list->right;
		}
	}
	return (list);
}
