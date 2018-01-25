/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_alloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:04:19 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/25 19:12:41 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int		free_args(t_flist **list)
{
	t_flist	*next;

	next = (*list)->left;
	ft_strdel(&((*list)->file->filename));
	ft_strdel(&((*list)->file->error));
	ft_strdel(&((*list)->file->path));
	if ((*list)->file->file_list != NULL)
	{
		free((*list)->file->file_list);
		(*list)->file->file_list = NULL;
	}
	free((*list)->file);
	free(*list);
	*list = NULL;
	if (next != NULL)
		free_args(&next);
	return (0);
}

void		free_files(t_list *files)
{
	t_list	*previous_file;

	while (files != NULL)
	{
		previous_file = files;
		files = files->next;
		free(previous_file->content);
		free(previous_file);
	}
}

void	free_file(t_file **file)
{
	if (*file != NULL)
	{
		ft_strdel(&((*file)->filename));
		ft_strdel(&((*file)->path));
		ft_strdel(&((*file)->error));
		if ((*file)->file_list != NULL)
		{
			free_flist(&((*file)->file_list));
			(*file)->file_list = NULL;
		}
		free(*file);
		*file = NULL;
	}
}

void		free_flist(t_flist **list_start)
{
	t_flist	*list;

	list = *list_start;
	free_file(&(list->file));
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
