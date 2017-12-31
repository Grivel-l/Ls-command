/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_alloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:04:19 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 01:15:41 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int		free_args(t_flist **list)
{
	t_flist	*next;

	next = (*list)->left;
	ft_strdel(&((*list)->file->filename));
	ft_strdel(&((*list)->file->path));
	free((*list)->file->file_list);
	free((*list)->file);
	free(*list);
	if (next != NULL)
		free_args(&next);
	return (0);
}

static void	free_file(t_file *file)
{
	if (file != NULL)
	{
		ft_strdel(&(file->filename));
		ft_strdel(&(file->path));
		if (file->file_list != NULL)
			free_flist(&(file->file_list));
		free(file);
		file = NULL;
	}
}

void		free_flist(t_flist **list_start)
{
	t_flist	*list;

	list = *list_start;
	free_file(list->file);
	if (list->left != NULL)
	{
		free(list->left);
		list->left = NULL;
	}
	if (list->right != NULL)
	{
		free(list->right);
		list->right = NULL;
	}
}
