/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 00:48:34 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 00:48:56 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_flist		*new_flist(t_file *file)
{
	t_flist	*list;

	if (file == NULL)
		return (NULL);
	if ((list = malloc(sizeof(t_flist))) == NULL)
		return (NULL);
	list->file = file;
	list->left = NULL;
	list->right = NULL;
	return (list);
}

int			browse_flist(t_flist **list, char *options,
				int (fun)(t_flist **list, char *options))
{
	if (*list == NULL)
		return (0);
	if ((*list)->right != NULL)
		browse_flist(&((*list)->right), options, fun);
	if (fun(list, options) == -1)
		return (-1);
	if ((*list)->left != NULL)
		browse_flist(&((*list)->left), options, fun);
	return (0);
}

int			browse_flist_path(t_flist **list, char *options, char *path,
				int (fun)(t_flist **list, char *path, char *options))
{
	if (*list == NULL)
		return (0);
	if ((*list)->right != NULL)
		browse_flist_path(&((*list)->right), options, path, fun);
	if (fun(list, path, options) == -1)
		return (-1);
	if ((*list)->left != NULL)
		browse_flist_path(&((*list)->left), options, path, fun);
	return (0);
}
