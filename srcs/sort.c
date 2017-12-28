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

t_flist	*set_flist_link(t_flist **list_start, t_list *files, char *path)
{
	t_flist	*list;

	list = *list_start;
	while (list != NULL)
	{
		if (ft_strcmp(list->file->filename, files->content) < 0)
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
