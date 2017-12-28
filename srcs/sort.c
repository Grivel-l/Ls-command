/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/26 23:54:59 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/27 00:11:16 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_list(t_flist **list, char *options)
{
	(void)list;
	(void)options;
}

static int	sort_time(t_file *file, t_list *target)
{
	(void)file;
	(void)target;
	return (0);
}

static int sort_alpha(t_file *file, t_list *target)
{
	return (ft_strcmp_ci(file->filename, target->content));
}

static int	sort(t_file *file, t_list *target, size_t time_sort)
{
	size_t	are_equal;

	are_equal = 0;
	if (time_sort)
		are_equal = sort_time(file, target);
	if (are_equal == 0)
		return (sort_alpha(file, target));
	else
		return (are_equal);
}

t_flist	*set_flist_link(t_flist **list_start,
				t_list *files, char *path, char *options)
{
	t_flist	*list;

	list = *list_start;
	while (list != NULL)
	{
		if (sort(list->file, files, ft_strchr(options, 't') != NULL) < 0)
		{
			if (list->left == NULL)
			{
				if ((list->left =
			new_flist(new_file(files->content, path, 0))) == NULL)
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
			new_flist(new_file(files->content, path, 0))) == NULL)
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
